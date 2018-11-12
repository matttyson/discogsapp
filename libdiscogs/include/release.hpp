/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "base_classes.hpp"
#include "paginate.hpp"

namespace discogs {
namespace parser {

class release {
public:
	release():year(0),id(0),num_for_sale(0),master_id(0),format_quantity(0),estimated_weight(0),lowest_price(0.0){}
	~release(){}
	release(const release &rhs) = default;
	release(release &&rhs) noexcept = default;
	release& operator=(const release &rhs) = default;
	release& operator=(release &&rhs) noexcept = default;

	int year;
	int id;
	int num_for_sale;
	int master_id;
	int format_quantity;
	int estimated_weight;
	double lowest_price;
	platform::string_t artists_sort;
	platform::string_t country;
	platform::string_t notes;
	platform::string_t thumb;
	platform::string_t title;
	platform::string_t date_changed;
	platform::string_t status;
	platform::string_t released_formatted;
	platform::string_t master_url;
	platform::string_t released;
	platform::string_t date_added;
	platform::string_t uri;
	platform::string_t resource_url;
	platform::string_t data_quality;
	common::community community_;
	std::vector<common::series> series_;
	std::vector<platform::string_t> styles;
	std::vector<platform::string_t> genres;
	std::vector<common::video> videos;
	std::vector<common::label> labels;
	std::vector<common::artist> artists;
	std::vector<common::image> images;
	std::vector<common::track> tracklist;
	std::vector<common::artist> extra_artists;
	std::vector<common::company> companies;
	std::vector<common::format> formats;
	std::vector<common::identifier> identifiers;
};

} // namespace discogs
} // namespace parser
