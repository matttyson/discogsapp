add_library(libdiscogs STATIC
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.cpp
	${CMAKE_CURRENT_LIST_DIR}/libdiscogs.hpp
)

target_include_directories(libdiscogs PUBLIC .)
target_include_directories(libdiscogs PUBLIC include)

target_include_directories(libdiscogs PRIVATE parsers)
target_include_directories(libdiscogs PRIVATE ..)

find_package(RapidJSON REQUIRED)

target_compile_definitions(libdiscogs PRIVATE
	RAPIDJSON_HAS_CXX11_TYPETRAITS
	RAPIDJSON_HAS_CXX11_NOEXCEPT
	RAPIDJSON_HAS_STDSTRING
)

find_package(RapidJSON REQUIRED)
target_include_directories(libdiscogs PRIVATE ${RAPIDJSON_INCLUDE_DIR})

if(WIN32)
	target_include_directories(libdiscogs PRIVATE ${CPPRESTSDK_INCLUDE_DIR})
	target_compile_options(libdiscogs PRIVATE /permissive-)
	# For linking against a static cpprestsdk on windows
	set_property(TARGET libdiscogs APPEND PROPERTY COMPILE_DEFINITIONS _NO_ASYNCRTIMP)
endif()

add_subdirectory(parsers)
add_subdirectory(include)
