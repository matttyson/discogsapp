include_directories(..)
include_directories(include)

add_library(libdiscogs STATIC
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.cpp
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.hpp
)

find_package(RapidJSON REQUIRED)

target_compile_definitions(libdiscogs PRIVATE
	RAPIDJSON_HAS_CXX11_TYPETRAITS
	RAPIDJSON_HAS_CXX11_NOEXCEPT
	RAPIDJSON_HAS_STDSTRING
)

find_package(RapidJSON REQUIRED)
target_include_directories(libdiscogs PRIVATE ${RAPIDJSON_INCLUDE_DIRS})

if(WIN32)
	target_compile_options(libdiscogs PRIVATE /permissive-)
	# For linking against a static cpprestsdk on windows
	set_property(TARGET libdiscogs APPEND PROPERTY COMPILE_DEFINITIONS _NO_ASYNCRTIMP)
endif()

add_subdirectory(parsers)


set_property(SOURCE "${CMAKE_CURRENT_LIST_DIR}/parsers/parser.cpp" APPEND PROPERTY
	INCLUDE_DIRECTORIES
		"${CMAKE_CURRENT_LIST_DIR}/include"
		"${CMAKE_CURRENT_LIST_DIR}/private_include")
