#include "porting.h"

#include "libdiscogs.hpp"

#include "include/folder_releases.hpp"
#include "parsers/folder_releases_parser.hpp"
#include "include/wantlist.hpp"
#include "parsers/wantlist_parser.hpp"
#include "include/collection.hpp"
#include "parsers/collection_parser.hpp"
#include "include/release.hpp"
#include "parsers/release_parser.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/oauth1.h>
#include <cpprest/details/basic_types.h>

#include <rapidjson/writer.h>


#include <memory>
#include <fstream>

namespace discogs {

template <typename Encoding>
class StdStringBuffer {
public:
	typedef typename Encoding::Ch Ch;

	StdStringBuffer() {}

	void Put(Ch c) { str.push_back(c); }

	void Flush() {}

	std::basic_string<Ch>&& MoveStdString() { return std::move(str); }

private:
	std::basic_string<Ch> str;
};


typedef StdStringBuffer<rapidjson::UTF8<> > Utf8StdStringBuffer;

#ifdef DISCOGS_WCHAR
typedef rapidjson::Writer<Utf8StdStringBuffer, rapidjson::UTF16<>, rapidjson::UTF8<>> Utf8StdStringWriter;
#else
typedef rapidjson::Writer<Utf8StdStringBuffer, rapidjson::UTF8<>, rapidjson::UTF8<>> Utf8StdStringWriter;
#endif

}

const static std::string json_content_type = std::string("application/json; charset=utf-8", 31);

using namespace web;
using namespace discogs::parser;


namespace discogs {

class rest_private {
public:
	rest_private(int per_page, const string_t &user_agent, const string_t &base_url)
		:m_per_page(per_page), m_user_agent(user_agent), m_base_url(base_url), m_client(base_url)
	{}

	int m_per_page;
	string_t m_user_agent;
	string_t m_base_url;

	// HTTP Client object
	web::http::client::http_client m_client;
};

}


discogs::rest::rest(const string_t & user_agent, const string_t & base_url)
	:m_private(new discogs::rest_private(100, user_agent, base_url))
{
}

discogs::rest::~rest()
{
}

int discogs::rest::per_page()const
{
	return m_private->m_per_page;
}

void discogs::rest::set_per_page(int per_page)
{
	m_private->m_per_page = per_page;
}

void discogs::rest::oauth_configure(
	const discogs::oauth1_data &data,
	const string_t &user_access_token,
	const string_t &user_secret_token
)
{
	web::http::oauth1::experimental::oauth1_config oauth1_config(
		data.consumer_key,
		data.consumer_secret,
		data.temp_endpoint,
		data.auth_endpoint,
		data.token_endpoint,
		data.callback_uri,
		web::http::oauth1::experimental::oauth1_methods::plaintext
	);

	// Set the user's access token, if we have it.
	if(user_access_token.size() && user_secret_token.size()){
		oauth1_config.set_token(web::http::oauth1::experimental::oauth1_token(
			user_access_token, user_secret_token
		));
	}

	web::http::client::http_client_config http_config;

	http_config.set_oauth1(oauth1_config);

	m_private->m_client = web::http::client::http_client(
		m_private->m_base_url, http_config
	);
}

http::http_request discogs::rest::create_request(
	const uri_builder &url,
	const http::method &method
)
{
	http::http_request request(method);
	request.set_request_uri(url.to_string());

	request.headers().add(STR("User-Agent"), m_private->m_user_agent);
	request.headers().add(STR("Accept"),
		STR("application/vnd.discogs.v2.discogs+json"));

	return request;
}

static pplx::task<utility::string_t>
//do_basic_get(pplx::task<http::http_response> response_task)
do_basic_get(http::http_response response)
{
	if (response.status_code() == http::status_codes::OK) {
		return (response.extract_string());
	}

	throw http::http_exception(response.status_code(), response.reason_phrase());
}

template <typename Parser>
static pplx::task<std::shared_ptr<Parser>>
do_basic_parse(utility::string_t str)
{
	/*
	dcout << str << "\n";
	std::ofstream file;
	file.open("parse.json");
	file << str;
	file.close();
	*/

	std::shared_ptr<Parser> p = std::make_shared<Parser>();
	rapidjson::GenericReader<
		rjs_UTF_t, rjs_UTF_t> r;
	rapidjson::GenericStringStream<rjs_UTF_t>
		iss(str.c_str());

//	Code for insitu parsing - not using at the moment.
//	rapidjson::GenericInsituStringStream<rjs_UTF_t>
//		iss(const_cast<char_t*>(str.c_str()));
//	rapidjson::ParseResult pr = r.Parse<rapidjson::kParseInsituFlag>(iss, *p);

	rapidjson::ParseResult pr = r.Parse(iss, *p);

	// TODO: Throw an exception here if nothing happens.

	if(pr.IsError()){
		discogs::dofstream file("parse_error.json");
		file << str;
		dcerr << STR("Parse Error! - json document written to parse_error.json") << dendl;
	}

	return pplx::task_from_result(p);
}

pplx::task<discogs::parser::release *>
discogs::rest::release(int release_id)
{
	uri_builder builder;

	builder.append_path(STR("releases"))
		.append_path(to_string_t(release_id));

	auto request = create_request(builder);
	auto response = m_private->m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<discogs::parser::release_parser>)
		.then([](pplx::task<std::shared_ptr<discogs::parser::release_parser>> task_p) ->
			pplx::task<discogs::parser::release *>
	{
		auto p = task_p.get();
		return pplx::task_from_result(
			new discogs::parser::release(std::move(p->release_))
		);
	});
}


pplx::task<discogs::parser::folder_list *>
discogs::rest::collection(const string_t & username)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"));

	auto request = create_request(builder);

	auto response = m_private->m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<parser::collection_parser>)
		.then([](pplx::task<std::shared_ptr<parser::collection_parser>> task_p) ->
			pplx::task<discogs::parser::folder_list *>
	{
		auto p = task_p.get();
		return pplx::task_from_result(
			new discogs::parser::folder_list(std::move(p->folder_list_))
		);
	});
}



pplx::task<discogs::parser::wantlist *>
discogs::rest::wantlist(
	const string_t &username,
	int page_id
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"));

	if (m_private->m_per_page > 0) {
		builder.append_query(STR("per_page"), m_private->m_per_page);
	}

	builder.append_query(STR("page"), page_id);

	builder.append_query(STR("sort"), STR("title"));

	auto request = create_request(builder);

	auto response = m_private->m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<discogs::parser::wantlist_parser>)
		.then([](std::shared_ptr<discogs::parser::wantlist_parser> p) ->
			pplx::task<discogs::parser::wantlist *>
	{
		return pplx::task_from_result(
			new discogs::parser::wantlist(std::move(p->wantlist_))
		);
	});
}



pplx::task<discogs::parser::folder_releases *>
discogs::rest::folder_releases(
	const string_t & username,
	const string_t &folder_id,
	int page_id)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"))
		.append_path(folder_id, true)
		.append_path(STR("releases"));

	if(m_private->m_per_page > 0){
		builder.append_query(STR("per_page"), m_private->m_per_page);
	}
	if(page_id > 0){
		builder.append_query(STR("page"), page_id);
	}

	auto request = create_request(builder);

	auto z = m_private->m_client.request(request);
	return z.then(do_basic_get)
			.then(do_basic_parse<parser::folder_releases_parser>)
			.then([](std::shared_ptr<parser::folder_releases_parser> p) ->
				pplx::task<parser::folder_releases *>
	{
		return pplx::task_from_result(
			new discogs::parser::folder_releases(std::move(p->folder_release))
		);
	});
}


pplx::task<bool>
discogs::rest::wantlist_delete(
	int release_id,
	const string_t &username
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username,true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	auto request = create_request(builder, http::methods::DEL);

	auto result = m_private->m_client.request(request);

	return
	result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == http::status_codes::NoContent){
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}

pplx::task<bool>
discogs::rest::wantlist_add(
	int release_id,
	const string_t &username
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	auto request = create_request(builder, http::methods::PUT);

	auto result = m_private->m_client.request(request);

	return result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == http::status_codes::Created){
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}


pplx::task<bool>
discogs::rest::wantlist_update(
	int release_id,
	const string_t &username,
	const string_t &notes,
	int rating
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	Utf8StdStringBuffer sb;
	Utf8StdStringWriter writer(sb);

	writer.StartObject();

	if(notes.length() > 0){
		writer.Key(STR("notes"), 5);
		writer.String(notes);
	}

	if(rating > -1){
		writer.Key(STR("rating"), 6);
		writer.Int(rating);
	}

	writer.EndObject();

	auto request = create_request(builder, http::methods::POST);
	request.set_body(sb.MoveStdString(), json_content_type);

	auto result = m_private->m_client.request(request);

	return result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == http::status_codes::OK){
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}
