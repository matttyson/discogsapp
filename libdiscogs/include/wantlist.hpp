/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {

class wantlist {
public:
	wantlist(){}
	wantlist
		(paginate::pagination &&pages__, std::vector<common::want> &&want___) noexcept
		:pages(pages__), want_(want___) {}
	~wantlist(){}
	wantlist(const wantlist &rhs) = default;
	wantlist(wantlist &&rhs) noexcept = default;
	wantlist& operator=(const wantlist &rhs) = default;
	wantlist& operator=(wantlist &&rhs) noexcept = default;

	paginate::pagination pages;
	std::vector<common::want> want_;
};

} // namespace discogs
} // namespace parser
