/* clang-format off */
/* Autogenerated.  Do not edit. */

#pragma once

#include "class_common.hpp"

namespace discogs {
namespace parser {
namespace collection {

class folder {
public:
	folder(): id(0), count(0) {}
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

class container {
public:
	container(){}
	container(std::vector<folder> &&folder__) noexcept
		:folders_(std::move(folder__))  {}
	container(const container &rhs) = default;
	container(container &&rhs) noexcept = default;
	container& operator=(const container &rhs) = default;
	container& operator=(container &&rhs) noexcept = default;

	std::vector<folder> folders_;

};

} // namespace discogs
} // namespace parser
} // namespace collection

/* clang-format on */
