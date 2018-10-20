/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"

namespace discogs {
namespace parser {
namespace collection {

class folder {
public:
	folder() :id(0), count(0) {}
	~folder() {}
	folder(const folder &rhs) = default;
	folder(folder &&rhs) noexcept = default;
	folder& operator=(const folder &rhs) = default;
	folder& operator=(folder &&rhs) noexcept = default;

	int id;
	int count;
	string_t resource_url;
	string_t name;
};

} // namespace discogs
} // namespace parser
} // namespace collection
