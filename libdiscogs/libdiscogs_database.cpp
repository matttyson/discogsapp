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
