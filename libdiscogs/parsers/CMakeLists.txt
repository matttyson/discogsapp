target_sources(libdiscogs PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/folder_releases.cpp
	${CMAKE_CURRENT_LIST_DIR}/folder_response.cpp
	${CMAKE_CURRENT_LIST_DIR}/folder_collection_releases.cpp
	${CMAKE_CURRENT_LIST_DIR}/collection_add_response.cpp
	${CMAKE_CURRENT_LIST_DIR}/wantlist.cpp
	${CMAKE_CURRENT_LIST_DIR}/collection.cpp
	${CMAKE_CURRENT_LIST_DIR}/release.cpp
	${CMAKE_CURRENT_LIST_DIR}/identity.cpp
	${CMAKE_CURRENT_LIST_DIR}/master.cpp
	${CMAKE_CURRENT_LIST_DIR}/search.cpp
	${CMAKE_CURRENT_LIST_DIR}/market_get.cpp
	${CMAKE_CURRENT_LIST_DIR}/market_listing.cpp


	${CMAKE_CURRENT_LIST_DIR}/folder_releases_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/folder_response_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/folder_collection_releases_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/collection_add_response_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/wantlist_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/collection_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/release_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/identity_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/master_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/search_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/market_get_parser.hpp
	${CMAKE_CURRENT_LIST_DIR}/market_listing_parser.hpp
)
