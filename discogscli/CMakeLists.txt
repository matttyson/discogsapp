# CMakeList.txt : CMake project for discogsapp, include source and define
# project specific logic here.
#
# https://floooh.github.io/2016/01/12/cmake-dependency-juggling.html

cmake_minimum_required (VERSION 3.8)

add_executable (discogsapp "discogsapp.cpp" "client.cpp" "cli_options.cpp")

target_sources(discogsapp PRIVATE client.hpp client_private.hpp)

target_link_libraries(discogsapp libdiscogs)

target_include_directories(discogsapp PRIVATE ..)

target_include_directories(discogsapp PRIVATE ${CXXOPTS_INCLUDE_DIR})


if(WIN32)
	target_compile_options(discogsapp PRIVATE /permissive-)
	target_include_directories(discogsapp PUBLIC ${CPPRESTSDK_INCLUDE_DIR})
	target_link_libraries(discogsapp ${CPPRESTSDK_LIBRARY})
	target_link_libraries(discogsapp ${ZLIB_LIBRARY})
	target_link_libraries(discogsapp winhttp bcrypt crypt32)
endif()


if(UNIX)
	find_package(OpenSSL REQUIRED)
	target_link_libraries(discogsapp ${OPENSSL_CRYPTO_LIBRARY})
	target_link_libraries(discogsapp cpprest pthread boost_system)
endif()

