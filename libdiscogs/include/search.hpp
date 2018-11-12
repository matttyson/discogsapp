/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "base_classes.hpp"
#include "paginate.hpp"

namespace discogs {
namespace result {

class mini_community {
public:
	mini_community():have(0),want(0){}
	~mini_community(){}
	mini_community(const mini_community &rhs) = default;
	mini_community(mini_community &&rhs) noexcept = default;
	mini_community& operator=(const mini_community &rhs) = default;
	mini_community& operator=(mini_community &&rhs) noexcept = default;

	int have;
	int want;
};


class result {
public:
	result():id(0),master_id(0){}
	~result(){}
	result(const result &rhs) = default;
	result(result &&rhs) noexcept = default;
	result& operator=(const result &rhs) = default;
	result& operator=(result &&rhs) noexcept = default;

	int id;
	int master_id;
	platform::string_t thumb;
	platform::string_t title;
	platform::string_t country;
	platform::string_t resource_url;
	platform::string_t type;
	platform::string_t uri;
	platform::string_t catno;
	platform::string_t year;
	platform::string_t cover_image;
	platform::string_t master_url;
	std::vector<platform::string_t> barcode;
	std::vector<platform::string_t> format;
	std::vector<platform::string_t> label;
	std::vector<platform::string_t> style;
	std::vector<platform::string_t> genre;
	mini_community community;
	parser::common::user_data user_data;
};


class search_results {
public:
	search_results(){}
	~search_results(){}
	search_results(const search_results &rhs) = default;
	search_results(search_results &&rhs) noexcept = default;
	search_results& operator=(const search_results &rhs) = default;
	search_results& operator=(search_results &&rhs) noexcept = default;

	parser::paginate::pagination pages;
	std::vector<result> results;
};

} // namespace discogs
} // namespace result
