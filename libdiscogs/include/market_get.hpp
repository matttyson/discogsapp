/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"
#include "market_classes.hpp"

namespace discogs {
namespace parser {

class market_listing {
public:
	market_listing(){}
	~market_listing(){}
	market_listing(const market_listing &rhs) = default;
	market_listing(market_listing &&rhs) noexcept = default;
	market_listing& operator=(const market_listing &rhs) = default;
	market_listing& operator=(market_listing &&rhs) noexcept = default;

	std::vector<common::listing> listings;
	paginate::pagination pages;
};

} // namespace discogs
} // namespace parser
