#pragma once
#include "class_common.hpp"

// Pagination support class for Discogs

namespace discogs {
namespace parser {
namespace paginate {

class urls {
public:
	urls() {}
	~urls() {}
	urls(const urls &rhs) = default;
	urls(urls &&rhs) noexcept = default;
	urls& operator=(const urls &rhs) = default;
	urls& operator=(urls &&rhs) noexcept = default;

	string_t next;
	string_t last;
	string_t first;
	string_t prev;
};


class pagination {
public:
	pagination() :per_page(0), items(0), page(0), pages(0) {}
	~pagination() {}
	pagination(const pagination &rhs) = default;
	pagination(pagination &&rhs) noexcept = default;
	pagination& operator=(const pagination &rhs) = default;
	pagination& operator=(pagination &&rhs) noexcept = default;

	int per_page;
	int items;
	int page;
	int pages;
	urls links;
};

} // namespace discogs
} // namespace parser
} // namespace paginate
