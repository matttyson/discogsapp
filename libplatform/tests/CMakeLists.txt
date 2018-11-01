find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(filetest filetest.cpp)
target_include_directories(filetest PRIVATE ..)
target_link_libraries(filetest ${GTEST_BOTH_LIBRARIES} libplatform)

add_test(filetests filetest)
