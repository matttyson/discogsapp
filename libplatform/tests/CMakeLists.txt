find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(openfiletest openfile.cpp)
target_include_directories(openfiletest PRIVATE ..)
target_link_libraries(openfiletest ${GTEST_BOTH_LIBRARIES} libplatform)

add_test(filetests openfiletest)
