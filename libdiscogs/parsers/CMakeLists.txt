target_sources(libdiscogs PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/folder_releases.cpp
	${CMAKE_CURRENT_LIST_DIR}/wantlist.cpp
)
target_include_directories(libdiscogs PRIVATE ../include)
