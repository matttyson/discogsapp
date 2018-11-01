#include "file.hpp"
#include "win32_helpers.hpp"

#include "gtest/gtest.h"

namespace {

const platform::string_t fname = STR("myfilename");

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

}
