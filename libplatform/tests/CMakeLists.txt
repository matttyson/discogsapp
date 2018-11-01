find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(filetest filetest.cpp utf_codes.hpp win32_helpers.hpp)
target_include_directories(filetest PRIVATE ..)
target_link_libraries(filetest ${GTEST_BOTH_LIBRARIES} libplatform)
add_test(filetests filetest)

add_executable(rapidjson_file rapidjson_file.cpp rapidjson_parser.hpp win32_helpers.hpp)
find_package(RapidJSON REQUIRED)
target_include_directories(rapidjson_file PRIVATE ${RAPIDJSON_INCLUDE_DIR})
target_include_directories(rapidjson_file PRIVATE ..)
target_link_libraries(rapidjson_file ${GTEST_BOTH_LIBRARIES} libplatform)
add_test(rapidjson rapidjson_file)
