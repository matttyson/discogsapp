#include "porting.h"

#include "libdiscogs.hpp"

#include "include/folder_releases.hpp"
#include "private_include/folder_releases_parser.hpp"
#include "include/collection.hpp"
#include "private_include/collection_parser.hpp"
#include "include/wantlist.hpp"
#include "private_include/wantlist_parser.hpp"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>

#include <rapidjson/writer.h>


#include <memory>

namespace discogs {

class DiscogsStringBuffer : public rapidjson::GenericStringBuffer<rapidjson::UTF8<>> {
public:
	std::string GetStdString() {
		return std::string(GetString(), GetLength());
	}
};

template <typename Encoding>
class StdStringBuffer {
public:
	typedef typename Encoding::Ch Ch;

	StdStringBuffer() {}

	void Put(Ch c) { str.push_back(c); }
	void PutUnsafe(Ch c) { str.push_back(c); }
	void Reserve(size_t sz) { str.reserve(sz); }

	void Flush() {}

	size_t GetSize() const { return str.capacity(); }
	size_t GetLength() const { return str.length(); }

	std::basic_string<Ch>&& MoveStdString() { return std::move(str); }

private:
	std::basic_string<Ch> str;
};

typedef StdStringBuffer<rapidjson::UTF8<> > Utf8StdStringBuffer;
typedef rapidjson::Writer<Utf8StdStringBuffer> Utf8StdStringWriter;

}

const static std::string json_content_type = std::string("application/json; charset=utf-8", 31);

using namespace discogs::parser;

discogs::rest::rest(const string_t & user_agent, const string_t & base_url)
	:m_per_page(100),m_user_agent(user_agent),m_client(base_url)
{
}

discogs::rest::~rest()
{
}

void discogs::rest::set_session_key(const string_t &session_key)
{
	m_session_key.reserve(session_key.length() + 15);
	m_session_key.clear();
	m_session_key.assign(STR("Discogs token="), 14);
	m_session_key.append(session_key);
}

web::http::http_request discogs::rest::create_request(
	const web::uri_builder &url,
	const web::http::method &method
)
{
	web::http::http_request request(method);
	request.set_request_uri(url.to_string());

	request.headers().add(STR("User-Agent"), m_user_agent);
	request.headers().add(STR("Accept"),
		STR("application/vnd.discogs.v2.discogs+json"));
	if (m_session_key.length() > 0) {
		request.headers().add(STR("Authorization"), m_session_key);
	}

	return request;
}

static pplx::task<utility::string_t>
//do_basic_get(pplx::task<web::http::http_response> response_task)
do_basic_get(web::http::http_response response)
{
	if (response.status_code() == web::http::status_codes::OK) {
		return (response.extract_string());
	}
	utility::string_t error = response.reason_phrase();
	throw std::runtime_error("boom");
	return pplx::task_from_result(string_t(STR("")));
}

template <typename Parser>
static pplx::task<std::shared_ptr<Parser>>
do_basic_parse(utility::string_t str)
{
	std::shared_ptr<Parser> p = std::make_shared<Parser>();
	rapidjson::GenericReader<
		discogs::parser::rjs_UTF_t, discogs::parser::rjs_UTF_t> r;
	rapidjson::GenericInsituStringStream<discogs::parser::rjs_UTF_t>
		iss(const_cast<char_t*>(str.c_str()));

	rapidjson::ParseResult pr = r.Parse<rapidjson::kParseInsituFlag>(iss, *p);

	return pplx::task_from_result(p);
}

pplx::task<discogs::parser::collection::container>
discogs::rest::collection(const string_t & username)
{
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"));

	auto request = create_request(builder);

	auto response = m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<collection::parser>)
		.then([](pplx::task<std::shared_ptr<collection::parser>> task_p) ->
			pplx::task<discogs::parser::collection::container>
	{
		auto p = task_p.get();
		return pplx::task_from_result(
			collection::container(
				std::move(p->folders_)
			)
		);
	});
}

pplx::task<discogs::parser::wantlist::container>
discogs::rest::wantlist(
	const string_t &username,
	int page_id
)
{
	auto sz = sizeof(pplx::task<discogs::parser::wantlist::container>);
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"));

	if (m_per_page > 0) {
		builder.append_query(STR("per_page"), m_per_page);
	}

	builder.append_query(STR("page"), page_id);

	builder.append_query(STR("sort"), STR("title"));

	auto request = create_request(builder);

	auto response = m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<wantlist::parser>)
		.then([](std::shared_ptr<wantlist::parser> p) ->
			pplx::task<wantlist::container>
	{
		return pplx::task_from_result(
			wantlist::container(
				std::move(p->wants_),
				std::move(p->pages)
			)
		);
	});
}



pplx::task<discogs::parser::folder_releases::container>
discogs::rest::folder_releases(
	const string_t & username,
	const string_t &folder_id,
	int page_id)
{
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"))
		.append_path(folder_id, true)
		.append_path(STR("releases"));

	if(m_per_page > 0){
		builder.append_query(STR("per_page"), m_per_page);
	}
	if(page_id > 0){
		builder.append_query(STR("page"), page_id);
	}

	auto request = create_request(builder);

	auto z = m_client.request(request);
	return z.then(do_basic_get)
			.then(do_basic_parse<folder_releases::parser>)
			.then([](std::shared_ptr<folder_releases::parser> p) ->
				pplx::task<folder_releases::container>
	{
		return pplx::task_from_result(
			folder_releases::container(
				std::move(p->release_),
				std::move(p->pages)
			)
		);
	});
}


pplx::task<bool>
discogs::rest::delete_wantlist(
	int release_id,
	const string_t &username
)
{
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username,true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	auto request = create_request(builder, web::http::methods::DEL);

	auto result = m_client.request(request);

	return
	result.then([](web::http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == web::http::status_codes::NoContent){
			return true;
		}

		throw std::runtime_error("Nope");
		return false;
	});
}

pplx::task<bool>
discogs::rest::add_wantlist(
	int release_id,
	const string_t &username
)
{
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	auto request = create_request(builder, web::http::methods::PUT);

	auto result = m_client.request(request);

	return result.then([](web::http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == web::http::status_codes::Created){
			return true;
		}

		throw std::runtime_error("Nope");
		return false;
	});
}


pplx::task<bool>
discogs::rest::update_wantlist(
	int release_id,
	const string_t &username,
	const string_t &notes,
	int rating
)
{
	web::uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(to_string_t(release_id));

	Utf8StdStringBuffer sb;
	Utf8StdStringWriter writer(sb);

	writer.StartObject();

	if(notes.length() > 0){
		std::string narrow = utility::conversions::to_utf8string(notes);
		writer.Key("notes", 5);
		writer.String(narrow);
	}

	if(rating > -1){
		writer.Key("rating", 6);
		writer.Int(rating);
	}

	writer.EndObject();

	auto request = create_request(builder, web::http::methods::POST);
	request.set_body(sb.MoveStdString(), json_content_type);

	auto result = m_client.request(request);

	return result.then([](web::http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if(code == web::http::status_codes::OK){
			return true;
		}

		throw std::runtime_error("Nope");
		return false;
	});
}
