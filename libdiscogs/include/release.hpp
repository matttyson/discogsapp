/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {
namespace release {

class release {
public:
	release():year(0),id(0),num_for_sale(0),master_id(0),format_quantity(0),estimated_weight(0),lowest_price(0.0){}
	release
		(int year__, int id__, int num_for_sale__, int master_id__, int format_quantity__, int estimated_weight__, double lowest_price__, string_t &&artists_sort__, string_t &&country__, string_t &&notes__, string_t &&thumb__, string_t &&title__, string_t &&date_changed__, string_t &&status__, string_t &&released_formatted__, string_t &&master_url__, string_t &&released__, string_t &&date_added__, string_t &&uri__, string_t &&resource_url__, string_t &&data_quality__, common::community &&community___, std::vector<string_t> &&series__, std::vector<string_t> &&styles__, std::vector<string_t> &&genres__, std::vector<common::video> &&videos__, std::vector<common::label> &&labels__, std::vector<common::artist> &&artists__, std::vector<common::image> &&images__, std::vector<common::track> &&tracklist__, std::vector<common::artist> &&extra_artists__, std::vector<common::company> &&companies__, std::vector<common::format> &&formats__, std::vector<common::identifier> &&identifiers__) noexcept
		:year(year__), id(id__), num_for_sale(num_for_sale__), master_id(master_id__), format_quantity(format_quantity__), estimated_weight(estimated_weight__), lowest_price(lowest_price__), artists_sort(artists_sort__), country(country__), notes(notes__), thumb(thumb__), title(title__), date_changed(date_changed__), status(status__), released_formatted(released_formatted__), master_url(master_url__), released(released__), date_added(date_added__), uri(uri__), resource_url(resource_url__), data_quality(data_quality__), community_(community___), series(series__), styles(styles__), genres(genres__), videos(videos__), labels(labels__), artists(artists__), images(images__), tracklist(tracklist__), extra_artists(extra_artists__), companies(companies__), formats(formats__), identifiers(identifiers__) {}
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
	string_t artists_sort;
	string_t country;
	string_t notes;
	string_t thumb;
	string_t title;
	string_t date_changed;
	string_t status;
	string_t released_formatted;
	string_t master_url;
	string_t released;
	string_t date_added;
	string_t uri;
	string_t resource_url;
	string_t data_quality;
	common::community community_;
	std::vector<string_t> series;
	std::vector<string_t> styles;
	std::vector<string_t> genres;
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
} // namespace release
