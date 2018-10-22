/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {

class folder_release_item {
public:
	folder_release_item():id(0),instance_id(0),rating(0),folder_id(0){}
	folder_release_item
		(int id__, int instance_id__, int rating__, int folder_id__, string_t &&date_added__, std::vector<common::note> &&notes__, common::basic_information &&basic_information___) noexcept
		:id(id__), instance_id(instance_id__), rating(rating__), folder_id(folder_id__), date_added(date_added__), notes(notes__), basic_information_(basic_information___) {}
	~folder_release_item(){}
	folder_release_item(const folder_release_item &rhs) = default;
	folder_release_item(folder_release_item &&rhs) noexcept = default;
	folder_release_item& operator=(const folder_release_item &rhs) = default;
	folder_release_item& operator=(folder_release_item &&rhs) noexcept = default;

	int id;
	int instance_id;
	int rating;
	int folder_id;
	string_t date_added;
	std::vector<common::note> notes;
	common::basic_information basic_information_;
};


class folder_releases {
public:
	folder_releases(){}
	folder_releases
		(paginate::pagination &&pages__, std::vector<folder_release_item> &&release___) noexcept
		:pages(pages__), release_(release___) {}
	~folder_releases(){}
	folder_releases(const folder_releases &rhs) = default;
	folder_releases(folder_releases &&rhs) noexcept = default;
	folder_releases& operator=(const folder_releases &rhs) = default;
	folder_releases& operator=(folder_releases &&rhs) noexcept = default;

	paginate::pagination pages;
	std::vector<folder_release_item> release_;
};

} // namespace discogs
} // namespace parser
