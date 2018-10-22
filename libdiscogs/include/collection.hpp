/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"

namespace discogs {
namespace parser {

class folder {
public:
	folder():id(0),count(0){}
	folder
		(int id__, int count__, string_t &&resource_url__, string_t &&name__) noexcept
		:id(id__), count(count__), resource_url(resource_url__), name(name__) {}
	~folder(){}
	folder(const folder &rhs) = default;
	folder(folder &&rhs) noexcept = default;
	folder& operator=(const folder &rhs) = default;
	folder& operator=(folder &&rhs) noexcept = default;

	int id;
	int count;
	string_t resource_url;
	string_t name;
};


class folder_list {
public:
	folder_list(){}
	folder_list
		(std::vector<folder> &&folders__) noexcept
		:folders(folders__) {}
	~folder_list(){}
	folder_list(const folder_list &rhs) = default;
	folder_list(folder_list &&rhs) noexcept = default;
	folder_list& operator=(const folder_list &rhs) = default;
	folder_list& operator=(folder_list &&rhs) noexcept = default;

	std::vector<folder> folders;
};

} // namespace discogs
} // namespace parser
