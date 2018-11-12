/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace result {

class master {
public:
	master():id(0),year(0),num_for_sale(0),main_release(0),lowest_price(0.0){}
	~master(){}
	master(const master &rhs) = default;
	master(master &&rhs) noexcept = default;
	master& operator=(const master &rhs) = default;
	master& operator=(master &&rhs) noexcept = default;

	int id;
	int year;
	int num_for_sale;
	int main_release;
	double lowest_price;
	platform::string_t uri;
	platform::string_t title;
	platform::string_t versions_url;
	platform::string_t resource_url;
	platform::string_t data_quality;
	platform::string_t main_release_url;
	std::vector<platform::string_t> styles;
	std::vector<platform::string_t> genres;
	std::vector<parser::common::image> images;
	std::vector<parser::common::video> videos;
	std::vector<parser::common::artist> artists;
	std::vector<parser::common::track> tracklist;
};

} // namespace discogs
} // namespace result
