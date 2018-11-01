# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
	add_definitions(/D_UNICODE /DUNICODE)
	add_definitions(/D_CRT_SECURE_NO_DEPRECATE /D_CRT_SECURE_NO_WARNINGS /D_CRT_NONSTDC_NO_WARNINGS)
	add_definitions(/DPLATFORM_WCHAR)
endif()

project ("discogsapp" CXX)

if(${ENABLE_TESTS})
	include(CTest)
	enable_testing()
endif()

# Include sub-projects.
add_subdirectory ("discogscli")
add_subdirectory ("libdiscogs")
add_subdirectory ("liboauth1")
add_subdirectory ("libplatform")

