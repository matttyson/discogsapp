# CMakeList.txt : CMake project for discogsapp, include source and define
# project specific logic here.
#


# https://floooh.github.io/2016/01/12/cmake-dependency-juggling.html


cmake_minimum_required (VERSION 3.8)

add_executable (discogsapp "discogsapp.cpp" "client.cpp" "cli_options.cpp")

#set_property(SOURCE "client.cpp" APPEND PROPERTY COMPILE_DEFINITIONS RAPIDJSON_SSE42=1)
#set_property(SOURCE "client.cpp" APPEND PROPERTY COMPILE_DEFINITIONS RAPIDJSON_SSE42=1)

#set_property(SOURCE "${CMAKE_CURRENT_LIST_DIR}/parser.cpp" APPEND PROPERTY COMPILE_DEFINITIONS RAPIDJSON_SSE42=1)

include_directories(..)

find_package(RapidJSON REQUIRED)
target_link_libraries(discogsapp libdiscogs)


if(WIN32)
	add_definitions(/D_NO_ASYNCRTIMP)

	target_link_libraries(discogsapp ${CPPSDKLIB})
	target_link_libraries(discogsapp ${ZLIBLIB})
	target_link_libraries(discogsapp WinHttp bcrypt crypt32)

	include_directories(D:/Programming/cmake_packages/cxxopts/include)
	include_directories(D:/Programming/vcpkg/installed/x64-windows-static-md/include)

	target_compile_options(discogsapp PRIVATE /permissive-)
endif()

if(UNIX)
	find_package(OpenSSL REQUIRED)
	#find_package(cpprest REQUIRED)
	include_directories(/home/mtyson/code/cxxopts/include)
	target_link_libraries(discogsapp ${OPENSSL_CRYPTO_LIBRARY})
#	target_link_libraries(discogsapp ${OPENSSL_SSL_LIBRARY})
	target_link_libraries(discogsapp cpprest)
	target_link_libraries(discogsapp pthread)
	target_link_libraries(discogsapp boost_system)
endif()

include_directories(${RapidJSON_INCLUDE_DIR})

# TODO: Add tests and install targets if needed.
