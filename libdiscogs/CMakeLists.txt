include_directories(..)
include_directories(include)

add_library(libdiscogs STATIC)

target_sources(libdiscogs PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.cpp
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.hpp
)

#find_package(cpprestsdk REQUIRED)
find_package(RapidJSON REQUIRED)
include_directories(${RapidJSON_INCLUDE_DIR})

#include_directories(${cpprestsdk_INCLUDE_DIR})

if(WIN32)
	target_compile_options(libdiscogs PRIVATE /permissive-)
	add_definitions(/D_NO_ASYNCRTIMP)
	include_directories(D:/Programming/vcpkg/installed/x64-windows-static-md/include)
endif()


add_subdirectory(parsers)

set_property(SOURCE "${CMAKE_CURRENT_LIST_DIR}/parsers/parser.cpp" APPEND PROPERTY COMPILE_DEFINITIONS RAPIDJSON_SSE42 RAPIDJSON_HAS_CXX11_TYPETRAITS RAPIDJSON_HAS_CXX11_NOEXCEPT)
