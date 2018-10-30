

add_library(liboauth1 STATIC
	${CMAKE_CURRENT_LIST_DIR}/oauth1.cpp
	${CMAKE_CURRENT_LIST_DIR}/oauth1.hpp
	${CMAKE_CURRENT_LIST_DIR}/oauth1_listener.cpp
	${CMAKE_CURRENT_LIST_DIR}/oauth1_listener.hpp
)

target_include_directories(liboauth1 PRIVATE ..)

if(WIN32)
	target_include_directories(liboauth1 PRIVATE ${CPPRESTSDK_INCLUDE_DIR})
	target_compile_options(liboauth1 PRIVATE /permissive-)
	# For linking against a static cpprestsdk on windows
	set_property(TARGET liboauth1 APPEND PROPERTY COMPILE_DEFINITIONS _NO_ASYNCRTIMP)
endif()
