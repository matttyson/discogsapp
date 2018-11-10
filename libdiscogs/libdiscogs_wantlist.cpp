#include "libdiscogs.hpp"
#include "libdiscogs_private.hpp"


pplx::task<discogs::parser::wantlist *>
discogs::rest::wantlist(
	const platform::string_t &username,
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

pplx::task<bool>
discogs::rest::wantlist_delete(
	int release_id,
	const platform::string_t &username
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(platform::to_string_t(release_id));

	auto request = create_request(builder, http::methods::DEL);

	auto result = m_private->m_client.request(request);

	return
		result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if (code == http::status_codes::NoContent) {
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}

pplx::task<bool>
discogs::rest::wantlist_add(
	int release_id,
	const platform::string_t &username
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(platform::to_string_t(release_id));

	auto request = create_request(builder, http::methods::PUT);

	auto result = m_private->m_client.request(request);

	return result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if (code == http::status_codes::Created) {
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}


pplx::task<bool>
discogs::rest::wantlist_update(
	int release_id,
	const platform::string_t &username,
	const platform::string_t &notes,
	int rating
)
{
	uri_builder builder;

	builder.append_path(STR("users"))
		.append_path(username, true)
		.append_path(STR("wants"))
		.append_path(platform::to_string_t(release_id));

	Utf8StdStringBuffer sb;
	Utf8StdStringWriter writer(sb);

	writer.StartObject();

	if (notes.length() > 0) {
		writer.Key(STR("notes"), 5);
		writer.String(notes);
	}

	if (rating > -1) {
		writer.Key(STR("rating"), 6);
		writer.Int(rating);
	}

	writer.EndObject();

	auto request = create_request(builder, http::methods::POST);
	request.set_body(std::move(sb.str), json_content_type);

	auto result = m_private->m_client.request(request);

	return result.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if (code == http::status_codes::OK) {
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}
