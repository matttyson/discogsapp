#include "libdiscogs.hpp"
#include "libdiscogs_private.hpp"

pplx::task<discogs::parser::folder_list *>
discogs::rest::collection_folders(const platform::string_t & username)
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

pplx::task<discogs::parser::folder_response *>
discogs::rest::collection_folder_add(
	const platform::string_t &username,
	const platform::string_t &folder_name
)
{
	uri_builder builder;
	builder.append_path(STR("users"))
		.append_path(username)
		.append_path(STR("collection"))
		.append_path(STR("folders"));

	auto request = create_request(builder, web::http::methods::POST);

	Utf8StdStringBuffer sb;
	Utf8StdStringWriter writer{sb};

	writer.StartObject();
	writer.Key(STR("name"), 4);
	writer.String(folder_name);
	writer.EndObject();

	request.set_body(std::move(sb.str), json_content_type);

	auto result = m_private->m_client.request(request);

	return result.then(do_basic_get)
		.then(do_basic_parse<parser::folder_response_parser>)
		.then([](std::shared_ptr<parser::folder_response_parser> p) ->
		pplx::task<parser::folder_response *>
	{
		return pplx::task_from_result(
			new discogs::parser::folder_response(std::move(p->folder_response))
		);
	});

}

pplx::task<discogs::parser::folder_releases *>
discogs::rest::collection_folder_releases(
	const platform::string_t & username,
	const platform::string_t &folder_id,
	int page_id)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"))
		.append_path(folder_id, true)
		.append_path(STR("releases"));

	if (m_private->m_per_page > 0) {
		builder.append_query(STR("per_page"), m_private->m_per_page);
	}
	if (page_id > 0) {
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

