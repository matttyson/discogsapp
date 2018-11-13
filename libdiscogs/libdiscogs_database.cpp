#include "libdiscogs.hpp"
#include "libdiscogs_private.hpp"


pplx::task<discogs::parser::release *>
discogs::rest::release(int release_id)
{
	uri_builder builder;

	builder.append_path(STR("releases"))
		.append_path(platform::to_string_t(release_id));

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		discogs::parser::release_parser,
		discogs::parser::release
	>(response);
}

pplx::task<discogs::result::master *>
discogs::rest::master(int master_id)
{
	uri_builder builder;

	builder.append_path(STR("masters"))
		.append_path(platform::to_string_t(master_id));

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		result::master_parser,
		discogs::result::master
	>(response);
}

pplx::task<discogs::result::search_results *>
discogs::rest::search(
	const std::vector<std::pair<platform::string_t, platform::string_t>> &args,
	int page_id)
{
	uri_builder builder;

	builder.append_path(STR("database"))
		.append_path(STR("search"));

	for(const auto &t : args) {
		builder.append_query(t.first, t.second);
	}

	if(page_id > -1){
		builder.append_query(STR("page_id"), page_id);
	}

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		result::search_parser,
		result::search_results
	>(response);
}
