# CMakeList.txt : CMake project for discogsapp, include source and define
# project specific logic here.
#
# https://floooh.github.io/2016/01/12/cmake-dependency-juggling.html

cmake_minimum_required (VERSION 3.8)

add_executable (discogsapp "discogsapp.cpp" "client.cpp" "cli_options.cpp")


target_link_libraries(discogsapp libdiscogs)

target_include_directories(discogsapp PRIVATE ${CXXOPTSINC})
target_include_directories(discogsapp PRIVATE ${CPPSDKINC})
target_include_directories(discogsapp PRIVATE ..)


if(WIN32)
	target_link_libraries(discogsapp ${CPPSDKLIB})
	target_link_libraries(discogsapp ${ZLIBLIB})
	target_link_libraries(discogsapp WinHttp bcrypt crypt32)
	target_compile_options(discogsapp PRIVATE /permissive-)
endif()

if(UNIX)
	find_package(OpenSSL REQUIRED)
	target_link_libraries(discogsapp ${OPENSSL_CRYPTO_LIBRARY})
	target_link_libraries(discogsapp cpprest)
	target_link_libraries(discogsapp pthread)
	target_link_libraries(discogsapp boost_system)
endif()

# TODO: Add tests and install targets if needed.
