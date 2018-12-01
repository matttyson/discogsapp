#include "libdiscogs.hpp"
#include "libdiscogs_private.hpp"

#include "parsers/market_get_parser.hpp"
#include "parsers/market_listing_parser.hpp"

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

	auto response = m_private->do_request(builder);

	return return_task_response<
		discogs::parser::market_get_parser,
		discogs::parser::market_listing,
		rjsNumberAsStringFlag
	>(response);
}

pplx::task<discogs::parser::common::listing*>
discogs::rest::market_listing(
	int listing_id,
	const platform::string_t &curr_abbr
)
{
	uri_builder builder;

	builder.append_path(STR("marketplace"))
		.append_path(STR("listings"))
		.append_path(platform::to_string_t(listing_id));

	if(curr_abbr.length() > 0){
		builder.append_query(STR("curr_abbr"), curr_abbr);
	}

	auto response = m_private->do_request(builder);

	return return_task_response<
		discogs::parser::market_listing_parser,
		discogs::parser::common::listing,
		rjsNumberAsStringFlag
	>(response);
}
