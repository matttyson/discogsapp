# CMakeList.txt : CMake project for discogsapp, include source and define
# project specific logic here.
#
# https://floooh.github.io/2016/01/12/cmake-dependency-juggling.html

cmake_minimum_required (VERSION 3.8)

add_executable (discogsapp
	${CMAKE_CURRENT_LIST_DIR}/discogsapp.cpp
	${CMAKE_CURRENT_LIST_DIR}/cli_options.cpp
	${CMAKE_CURRENT_LIST_DIR}/client.cpp
	${CMAKE_CURRENT_LIST_DIR}/client.hpp
	${CMAKE_CURRENT_LIST_DIR}/client_private.hpp
	${CMAKE_CURRENT_LIST_DIR}/config.cpp
	${CMAKE_CURRENT_LIST_DIR}/config.hpp
	${CMAKE_CURRENT_LIST_DIR}/config_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/oauth1_data.cpp
	${CMAKE_CURRENT_LIST_DIR}/oauth1_data.hpp
	${CMAKE_CURRENT_LIST_DIR}/rapidjson_pretty.hpp
)

target_link_libraries(discogsapp libdiscogs liboauth1 libplatform)

target_include_directories(discogsapp PRIVATE ..)

target_include_directories(discogsapp PRIVATE ${CXXOPTS_INCLUDE_DIR})

find_package(RapidJSON REQUIRED)
target_include_directories(discogsapp PRIVATE ${RAPIDJSON_INCLUDE_DIR})

if(WIN32)
	target_compile_options(discogsapp PRIVATE /permissive-)
	target_include_directories(discogsapp PUBLIC ${CPPRESTSDK_INCLUDE_DIR})
	target_link_libraries(discogsapp ${CPPRESTSDK_LIBRARY})
	target_link_libraries(discogsapp ${ZLIB_LIBRARY})
	target_link_libraries(discogsapp winhttp bcrypt crypt32 Httpapi)
	target_sources(discogsapp PRIVATE ${CMAKE_CURRENT_LIST_DIR}/win32_browser.cpp)
endif()


if(UNIX)
	find_package(OpenSSL REQUIRED)
	target_link_libraries(discogsapp ${OPENSSL_CRYPTO_LIBRARY})
	target_link_libraries(discogsapp cpprest pthread boost_system)
	target_sources(discogsapp PRIVATE ${CMAKE_CURRENT_LIST_DIR}/linux_browser.cpp)
endif()

