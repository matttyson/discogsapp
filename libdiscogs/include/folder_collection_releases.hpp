/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {

class collection_release_item {
public:
	collection_release_item():id(0),instance_id(0),rating(0),folder_id(0){}
	~collection_release_item(){}
	collection_release_item(const collection_release_item &rhs) = default;
	collection_release_item(collection_release_item &&rhs) noexcept = default;
	collection_release_item& operator=(const collection_release_item &rhs) = default;
	collection_release_item& operator=(collection_release_item &&rhs) noexcept = default;

	int id;
	int instance_id;
	int rating;
	int folder_id;
	platform::string_t date_added;
	common::basic_information basic_information_;
};


class collection_release {
public:
	collection_release(){}
	~collection_release(){}
	collection_release(const collection_release &rhs) = default;
	collection_release(collection_release &&rhs) noexcept = default;
	collection_release& operator=(const collection_release &rhs) = default;
	collection_release& operator=(collection_release &&rhs) noexcept = default;

	paginate::pagination pages;
	std::vector<collection_release_item> releases;
};

} // namespace discogs
} // namespace parser
