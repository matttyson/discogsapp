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

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		parser::collection_parser,
		discogs::parser::folder_list
	>(response);
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

	auto request = m_private->create_request(builder, web::http::methods::POST);

	Utf8StdStringBuffer sb;
	Utf8StdStringWriter writer{sb};

	writer.StartObject();
	writer.Key(STR("name"), 4);
	writer.String(folder_name);
	writer.EndObject();

	request.set_body(std::move(sb.str), json_content_type);

	auto response = m_private->m_client.request(request);

	return return_task_response<
		parser::folder_response_parser,
		discogs::parser::folder_response
	>(response);
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

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		parser::folder_releases_parser,
		discogs::parser::folder_releases
	>(response);
}

pplx::task<discogs::parser::folder_response *>
discogs::rest::collection_folder(
	const platform::string_t &username,
	int folder_id
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"))
		.append_path(platform::to_string_t(folder_id));

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		parser::folder_response_parser,
		discogs::parser::folder_response
	>(response);
}

pplx::task<bool>
discogs::rest::collection_folder_delete(
	const platform::string_t &username,
	int folder_id
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("folders"))
		.append_path(platform::to_string_t(folder_id), false);

	auto request = m_private->create_request(builder, http::methods::DEL);
	auto response = m_private->m_client.request(request);

	return return_bool_response(response);
}

pplx::task< discogs::parser::collection_release *>
discogs::rest::collection_releases(
	const platform::string_t &username,
	int release_id
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("collection"))
		.append_path(STR("releases"))
		.append_path(platform::to_string_t(release_id));

	auto request = m_private->create_request(builder);
	auto response = m_private->m_client.request(request);

	return return_task_response<
		parser::folder_collection_releases_parser,
		discogs::parser::collection_release
	>(response);
}
