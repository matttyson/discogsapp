#include "libdiscogs.hpp"
#include "libdiscogs_private.hpp"

#include "parsers/market_get_parser.hpp"

pplx::task<discogs::parser::market_listing*>
discogs::rest::market_get(
	const platform::string_t &username,
	const platform::string_t &status,
	const platform::string_t &sort,
	const platform::string_t &sort_order
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("inventory"));

	if(status.length() > 0){
		builder.append_query(STR("status"), status);
	}
	if(status.length() > 0){
		builder.append_query(STR("sort"), sort);
	}
	if(status.length() > 0){
		builder.append_query(STR("sort_order"), sort_order);
	}

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		discogs::parser::market_get_parser,
		discogs::parser::market_listing
	>(response);
}
