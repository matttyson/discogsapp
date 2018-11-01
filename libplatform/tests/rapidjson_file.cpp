#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/reader.h>

#include "platform.hpp"
#include "platform_rjs.hpp"
#include "file.hpp"
#include "rapidjson_file.hpp"
#include "rapidjson_parser.hpp"

#include "win32_helpers.hpp"

#include <gtest/gtest.h>


/*
	Some tests for the platform RapidJSON reader / writer classes.

	These are pretty shitty at the moment.  I need to get some test
	data and make these a little more robust.
*/

TEST(RapidJSON, Writer) {

	platform::file f;
	char buffer[1024];

	const bool rc = f.open(fname,
		platform::file::io_mode::readwrite,
		platform::file::create_mode::trunc);

	ASSERT_TRUE(rc);

	platform::PlatformWriteStream pws(f, buffer, sizeof(buffer));

	rapidjson::Writer<
		platform::PlatformWriteStream,
		rjs_UTF_t,
		rapidjson::UTF8<>
	> writer(pws);

	writer.StartObject();
	writer.Key(STR("KEY"), 3);
	writer.String(STR("VALUE"), 5);
	writer.EndObject();

	f.close();
}

TEST(RapidJSON, Reader) {

	platform::file f;
	char buffer[1024];
	const bool rc = f.open(fname,
		platform::file::io_mode::readwrite,
		platform::file::create_mode::exist);
	ASSERT_TRUE(rc);

	rapidjson_test_parser parser;

	platform::PlatformReadStream prs(f, buffer, sizeof(buffer));
	rapidjson::GenericReader<rapidjson::UTF8<>, rjs_UTF_t> r;

	rapidjson::ParseResult pr = r.Parse(prs, parser);

	ASSERT_FALSE(pr.IsError());

}
