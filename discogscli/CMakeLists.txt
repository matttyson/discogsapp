# CMakeList.txt : CMake project for discogsapp, include source and define
# project specific logic here.
#
# https://floooh.github.io/2016/01/12/cmake-dependency-juggling.html

cmake_minimum_required (VERSION 3.8)

add_executable (discogsapp "discogsapp.cpp" "client.cpp" "cli_options.cpp")

target_link_libraries(discogsapp libdiscogs)

target_include_directories(discogsapp PRIVATE ..)

target_include_directories(discogsapp PRIVATE ${CXXOPTS_INCLUDE_DIR})


if(WIN32)
	find_package(cpprestsdk CONFIG REQUIRED)

	target_link_libraries(discogsapp PRIVATE
		cpprestsdk::cpprest
		cpprestsdk::cpprestsdk_zlib_internal
		cpprestsdk::cpprestsdk_boost_internal
		cpprestsdk::cpprestsdk_openssl_internal
	)

	target_link_libraries(discogsapp PRIVATE ${BOOST_SYSTEM_LIB})
endif()


if(UNIX)
	find_package(OpenSSL REQUIRED)
	target_link_libraries(discogsapp ${OPENSSL_CRYPTO_LIBRARY})
	target_link_libraries(discogsapp cpprest pthread boost_system)
endif()

