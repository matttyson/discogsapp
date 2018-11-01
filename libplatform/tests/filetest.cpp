#include "file.hpp"
#include "win32_helpers.hpp"
#include "utf_codes.hpp"

#include "gtest/gtest.h"

namespace {

// File should exist and contents preserved
TEST(OpenOpenTest, OpenExistingFile) {
	ASSERT_TRUE(create_junk_file(fname));
	ASSERT_TRUE(file_exists(fname));

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::open);

		ASSERT_EQ(f.length(), junk_size);
		char buffer[junk_size];
		f.read(buffer, junk_size);
		ASSERT_STREQ(buffer, junk_data);
	}

	ASSERT_TRUE(delete_file(fname));
}

// File should not exist and be created
TEST(OpenOpenTest, OpenNotExistingFile) {

	delete_file(fname);
	ASSERT_FALSE(file_exists(fname));

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::open);
		ASSERT_EQ(f.length(), 0);
	}

	ASSERT_TRUE(file_exists(fname));
	ASSERT_TRUE(delete_file(fname));

}


// Create mode test.  Create the file if it does not exist
// Error if it does exist.
// If the file does exist, the open should fail.
TEST(OpenCreateTest, OpenExistingFile){

	create_empty_file(fname);

	{
		platform::file f;

		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::create);

		ASSERT_FALSE(rc);
	}

	delete_file(fname);
}

// File should not exist and be created
TEST(OpenCreateTest, OpenNotExistingFile) {
	delete_file(fname);

	ASSERT_FALSE(file_exists(fname));
	{
		platform::file f;

		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::create);
		ASSERT_TRUE(rc);
	}

	ASSERT_TRUE(file_exists(fname));

	ASSERT_TRUE(delete_file(fname));
}


// File should exist on disk and contents should be destroyed
TEST(OpenTruncTest, OpenExistingFile){
	delete_file(fname);
	ASSERT_TRUE(create_junk_file(fname));
	ASSERT_GT(file_length(fname), 0);

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::trunc
		);
		ASSERT_TRUE(rc);

		ASSERT_EQ(f.length(), 0);
	}

	ASSERT_TRUE(file_exists(fname));
	ASSERT_EQ(file_length(fname), 0);

	delete_file(fname);
}

// File should not exist and be created
TEST(OpenTruncTest, OpenNotExistingFile) {
	delete_file(fname);

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::trunc
		);
		ASSERT_TRUE(rc);
	}

	ASSERT_TRUE(file_exists(fname));

	delete_file(fname);
}

// File open should succeed if the file does exist
TEST(OpenExistTest, OpenExistingFile) {
	delete_file(fname);
	create_empty_file(fname);

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::exist
		);
		ASSERT_TRUE(rc);
	}

	ASSERT_TRUE(file_exists(fname));

	delete_file(fname);
}

// File open should fail if the file does not exist.
TEST(OpenExistTest, OpenNotExistingFile) {
	delete_file(fname);

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::exist
		);
		ASSERT_FALSE(rc);
	}

	ASSERT_FALSE(file_exists(fname));
	delete_file(fname);
}

// Write a platform string out as UTF8
// Read in the UTF8 string as a platform string
// Make sure they are the same

TEST(ReadWrite, WriteUTF8) {
	delete_file(fname);

	{
		platform::file f;

		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::create);
		ASSERT_TRUE(rc);

		f.write_utf8(utf_code_string);
	}

	{
		platform::file f;

		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::exist);
		ASSERT_TRUE(rc);

		platform::string_t str;

		f.read_utf8(str);

		ASSERT_EQ(str, utf_code_string);
	}

	delete_file(fname);
}

TEST(ReadWrite, WriteBinary) {
	delete_file(fname);

	{
		platform::file f;

		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::create
		);

		ASSERT_TRUE(rc);

		const size_t sz = f.write((const char*)(utf_codes), sizeof(utf_codes));

		ASSERT_EQ(sz, sizeof(utf_codes));
	}

	ASSERT_EQ(file_length(fname), sizeof(utf_codes));

	{
		platform::file f;
		const bool rc = f.open(fname,
			platform::file::io_mode::readwrite,
			platform::file::create_mode::exist);
		ASSERT_TRUE(rc);

		platform::char_t buffer[utf_code_count];

		const size_t sz = f.read((char*)buffer, sizeof(buffer));

		ASSERT_EQ(sz, sizeof(buffer));

		const int cmp = memcmp(buffer, utf_codes, sizeof(buffer));
		ASSERT_EQ(cmp, 0);
	}

	delete_file(fname);
}

}
