/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {
namespace folder_release {

class release {
public:
	release():id(0),instance_id(0),rating(0),folder_id(0){}
	~release(){}
	release(const release &rhs) = default;
	release(release &&rhs) noexcept = default;
	release& operator=(const release &rhs) = default;
	release& operator=(release &&rhs) noexcept = default;

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
	folder_releases(std::vector<release> &&release__, paginate::pagination &&pages__) noexcept
		:release_(release__), pages(pages__)
	{}
	~folder_releases(){}
	folder_releases(const folder_releases &rhs) = default;
	folder_releases(folder_releases &&rhs) noexcept = default;
	folder_releases& operator=(const folder_releases &rhs) = default;
	folder_releases& operator=(folder_releases &&rhs) noexcept = default;

	paginate::pagination pages;
	std::vector<release> release_;
};

} // namespace discogs
} // namespace parser
} // namespace folder_release
