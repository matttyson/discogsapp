#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>
#include <rapidjson/stream.h>

#include "libplatform/platform_rjs.hpp"

#include <cpprest/details/basic_types.h>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>

#include "parsers/folder_releases_parser.hpp"
#include "parsers/folder_response_parser.hpp"
#include "parsers/folder_collection_releases_parser.hpp"
#include "parsers/collection_add_response_parser.hpp"
#include "parsers/wantlist_parser.hpp"
#include "parsers/collection_parser.hpp"
#include "parsers/release_parser.hpp"
#include "parsers/master_parser.hpp"
#include "parsers/identity_parser.hpp"
#include "parsers/search_parser.hpp"

#include <pplx/pplxtasks.h>

#include <memory>

using namespace web;
using namespace discogs::parser;

namespace discogs {

template <typename Encoding>
class StdStringBuffer {
public:
	typedef typename Encoding::Ch Ch;

	StdStringBuffer() {}

	void Put(Ch c) { str.push_back(c); }

	void Flush() {}

	std::basic_string<Ch> str;
};

typedef StdStringBuffer<rapidjson::UTF8<> > Utf8StdStringBuffer;


// https://github.com/Tencent/rapidjson/issues/852
// The upstream implementation of RawNumber writes out a quoted string which is a bit daft.
// Note that this implementation has no input validation, so we'd have to trust the user not
// to do something daft like supply something that isn't a number
template<
	typename OutputStream,
	typename SourceEncoding = rapidjson::UTF8<>,
	typename TargetEncoding = rapidjson::UTF8<>,
	typename StackAllocator = rapidjson::CrtAllocator,
	unsigned writeFlags = rapidjson::kWriteDefaultFlags>
class FixedRawNumberWriter : public rapidjson::Writer<OutputStream, SourceEncoding, TargetEncoding, StackAllocator, writeFlags> {
	using super_class = rapidjson::Writer<OutputStream, SourceEncoding, TargetEncoding, StackAllocator, writeFlags>;
public:
	explicit
	FixedRawNumberWriter(OutputStream &os, StackAllocator* stackAllocator = 0, size_t levelDepth = super_class::kDefaultLevelDepth)
	:super_class(os, stackAllocator, levelDepth)
	{
	}

	explicit
	FixedRawNumberWriter(StackAllocator* stackAllocator = 0, size_t levelDepth = super_class::kDefaultLevelDepth)
	:super_class(stackAllocator, levelDepth)
	{
	}

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS
	FixedRawNumberWriter(FixedRawNumberWriter&& rhs)
	:super_class(rhs)
	{
	}
#endif

	bool RawNumber(const typename super_class::Ch* str, rapidjson::SizeType length, bool copy = false) {
		RAPIDJSON_ASSERT(str != 0);
		(void)copy;
		super_class::Prefix(rapidjson::kNumberType);
		return super_class::EndValue(super_class::WriteRawValue(str, length));
	}
};


// When parsing numbers as strings, and we're using wide characters we need to parse
// insitu or we only get the first charater. This appears to be a bug in rapidjson.
// I've filed a bug upstream about this
// https://github.com/Tencent/rapidjson/issues/1412
constexpr rapidjson::ParseFlag rjsNumberAsStringFlag =
	static_cast<rapidjson::ParseFlag>(
		rapidjson::kParseDefaultFlags |
		rapidjson::kParseNumbersAsStringsFlag |
		rapidjson::kParseInsituFlag
	);


#ifdef PLATFORM_WCHAR
typedef FixedRawNumberWriter<Utf8StdStringBuffer, rapidjson::UTF16<>, rapidjson::UTF8<>> Utf8StdStringWriter;
#else
typedef FixedRawNumberWriter<Utf8StdStringBuffer, rapidjson::UTF8<>, rapidjson::UTF8<>> Utf8StdStringWriter;
#endif

extern const std::string json_content_type;

class rest_private {
public:
	rest_private(int per_page, const platform::string_t &user_agent, const platform::string_t &base_url)
		:m_per_page(per_page), m_user_agent(user_agent), m_base_url(base_url), m_client(base_url)
	{}


	http::http_request create_request(
		const web::http::uri_builder &url,
		const web::http::method &method = web::http::methods::GET
	);


	int m_per_page;
	platform::string_t m_user_agent;
	platform::string_t m_base_url;

	// HTTP Client object
	web::http::client::http_client m_client;
};


static pplx::task<utility::string_t>
do_basic_get(http::http_response response)
{
	if (response.status_code() == http::status_codes::OK) {
		return (response.extract_string());
	}
	else if (response.status_code() == http::status_codes::Created){
		return (response.extract_string());
	}

	throw http::http_exception(response.status_code(), response.reason_phrase());
}

template <typename Parser,
	rapidjson::ParseFlag PARSEFLAGS = rapidjson::kParseDefaultFlags>
static pplx::task<std::shared_ptr<Parser>>
do_basic_parse(utility::string_t str)
{
	std::shared_ptr<Parser> p = std::make_shared<Parser>();

	rapidjson::GenericReader<rjs_UTF_t, rjs_UTF_t> r;


	rapidjson::GenericInsituStringStream<rjs_UTF_t>
		iss(const_cast<rjs_UTF_t::Ch*>(str.c_str()));
	rapidjson::ParseResult pr = r.Parse<PARSEFLAGS>(iss, *p);

	if (pr.IsError()) {
		platform::dofstream file("parse_error.json");
		file << str;
		dcerr << STR("Parse Error! - json document written to parse_error.json") << dendl;
	}

	return pplx::task_from_result(p);
}


template <typename PARSER, typename RESPONSE,
	rapidjson::ParseFlag PARSEFLAGS = rapidjson::kParseDefaultFlags
>
static pplx::task<RESPONSE *>
return_task_response(const pplx::task<http::http_response> &response)
{
	return response.then(do_basic_get)
		.then(do_basic_parse<PARSER, PARSEFLAGS>)
		.then([](pplx::task<std::shared_ptr<PARSER>> task_p) ->
			pplx::task<RESPONSE *>
	{
		auto p = task_p.get();
		return pplx::task_from_result(
			new RESPONSE(std::move(p->RESULT))
		);
	});
}

static pplx::task<bool>
return_bool_response(const pplx::task<http::http_response> &response)
{
	return
		response.then([](http::http_response resp) -> bool {
		const auto code = resp.status_code();

		if (code == http::status_codes::NoContent) {
			return true;
		}

		throw http::http_exception(resp.status_code(), resp.reason_phrase());
	});
}

}
