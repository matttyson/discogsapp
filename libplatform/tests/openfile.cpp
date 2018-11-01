#include "file.hpp"

#include "gtest/gtest.h"

namespace {

// File should exist and contents preserved
TEST(OpenOpenTest, OpenExistingFile) {
	platform::file f;
}

// File should not exist and be created
TEST(OpenOpenTest, OpenNewFile) {

}


// Should error if the file does not exist
TEST(OpenCreateTest, OpenExistingFile){

}

// File should not exist and be created
TEST(OpenCreateTest, OpenNewFile) {

}


// File should exist on disk and contents should be destroyed
TEST(OpenTruncTest, OpenExistingFile){

}

// File should not exist and be created
TEST(OpenTruncTest, OpenNewFile) {

}

}
