add_library(libplatform STATIC
	${CMAKE_CURRENT_LIST_DIR}/file.hpp
	${CMAKE_CURRENT_LIST_DIR}/platform.hpp
	${CMAKE_CURRENT_LIST_DIR}/exception.hpp
)

if(WIN32)
	target_sources(libplatform PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/win32_file.cpp
		${CMAKE_CURRENT_LIST_DIR}/win32_platform.cpp
	)
endif()

if(UNIX)
	target_sources(libplatform PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/linux_file.cpp
	)
endif()
