#include "libplatform/platform.hpp"

#include "libdiscogs.hpp"

#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/oauth1.h>

#include "libdiscogs_private.hpp"

namespace discogs {

const std::string json_content_type = std::string("application/json; charset=utf-8", 31);

}

discogs::rest::rest(const platform::string_t & user_agent, const platform::string_t & base_url)
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
	const platform::string_t &user_access_token,
	const platform::string_t &user_secret_token
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


pplx::task<discogs::parser::identity *>
discogs::rest::identity()
{
	uri_builder builder;

	builder.append_path(STR("oauth"))
		.append_path(STR("identity"));

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return response.then(do_basic_get)
		.then(do_basic_parse<discogs::parser::identity_parser>)
		.then([](pplx::task<std::shared_ptr<discogs::parser::identity_parser>> task_p) ->
			pplx::task<discogs::parser::identity *>
	{
		auto p = task_p.get();
		return pplx::task_from_result(
			new discogs::parser::identity(std::move(p->identity_))
		);
	});
}

pplx::task<platform::string_t>
discogs::rest::download_url(const platform::string_t &url_path)
{
	uri_builder builder;
	builder.append_path(url_path);

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return response.then(do_basic_get);
}


// No longer a class method.  Just a standalone function
// to create a request with the variables we need already set.
http::http_request discogs::rest_private::create_request(
	const uri_builder &url,
	const http::method &method
)
{
	http::http_request request(method);
	request.set_request_uri(url.to_string());

	request.headers().add(STR("User-Agent"), this->m_user_agent);
	request.headers().add(STR("Accept"),
		STR("application/vnd.discogs.v2.discogs+json"));

	return request;
}
