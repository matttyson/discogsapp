#pragma once
#include "class_common.hpp"

// Classes that can be reused in most endpoints

namespace discogs {
namespace parser {
namespace common {

class user_data {
public:
	user_data():in_collection(false),in_wantlist(false){}
	~user_data(){}
	user_data(const user_data &rhs) = default;
	user_data(user_data &&rhs) noexcept = default;
	user_data& operator=(const user_data &rhs) = default;
	user_data& operator=(user_data &&rhs) noexcept = default;

	bool in_collection;
	bool in_wantlist;
};


class contributor {
public:
	contributor(){}
	~contributor(){}
	contributor(const contributor &rhs) = default;
	contributor(contributor &&rhs) noexcept = default;
	contributor& operator=(const contributor &rhs) = default;
	contributor& operator=(contributor &&rhs) noexcept = default;

	platform::string_t username;
	platform::string_t resource_url;
};


class identifier {
public:
	identifier(){}
	~identifier(){}
	identifier(const identifier &rhs) = default;
	identifier(identifier &&rhs) noexcept = default;
	identifier& operator=(const identifier &rhs) = default;
	identifier& operator=(identifier &&rhs) noexcept = default;

	platform::string_t type;
	platform::string_t value;
	platform::string_t description;
};


class label {
public:
	label():id(0){}
	~label(){}
	label(const label &rhs) = default;
	label(label &&rhs) noexcept = default;
	label& operator=(const label &rhs) = default;
	label& operator=(label &&rhs) noexcept = default;

	int id;
	platform::string_t name;
	platform::string_t entity_type;
	platform::string_t catno;
	platform::string_t resource_url;
	platform::string_t entity_type_name;
};


class video {
public:
	video():duration(0),embed(false){}
	~video(){}
	video(const video &rhs) = default;
	video(video &&rhs) noexcept = default;
	video& operator=(const video &rhs) = default;
	video& operator=(video &&rhs) noexcept = default;

	int duration;
	bool embed;
	platform::string_t description;
	platform::string_t title;
	platform::string_t uri;
};


class company {
public:
	company():id(0){}
	~company(){}
	company(const company &rhs) = default;
	company(company &&rhs) noexcept = default;
	company& operator=(const company &rhs) = default;
	company& operator=(company &&rhs) noexcept = default;

	int id;
	platform::string_t name;
	platform::string_t entity_type;
	platform::string_t catno;
	platform::string_t resource_url;
	platform::string_t entity_type_name;
};


class rating {
public:
	rating():count(0),average(0.0){}
	~rating(){}
	rating(const rating &rhs) = default;
	rating(rating &&rhs) noexcept = default;
	rating& operator=(const rating &rhs) = default;
	rating& operator=(rating &&rhs) noexcept = default;

	int count;
	double average;
};


class submitter {
public:
	submitter(){}
	~submitter(){}
	submitter(const submitter &rhs) = default;
	submitter(submitter &&rhs) noexcept = default;
	submitter& operator=(const submitter &rhs) = default;
	submitter& operator=(submitter &&rhs) noexcept = default;

	platform::string_t username;
	platform::string_t resource_url;
};


class artist {
public:
	artist():id(0){}
	~artist(){}
	artist(const artist &rhs) = default;
	artist(artist &&rhs) noexcept = default;
	artist& operator=(const artist &rhs) = default;
	artist& operator=(artist &&rhs) noexcept = default;

	int id;
	platform::string_t join;
	platform::string_t name;
	platform::string_t anv;
	platform::string_t tracks;
	platform::string_t role;
	platform::string_t resource_url;
};


class image {
public:
	image():height(0),width(0){}
	~image(){}
	image(const image &rhs) = default;
	image(image &&rhs) noexcept = default;
	image& operator=(const image &rhs) = default;
	image& operator=(image &&rhs) noexcept = default;

	int height;
	int width;
	platform::string_t uri;
	platform::string_t resource_url;
	platform::string_t type;
	platform::string_t uri150;
};


class track {
public:
	track(){}
	~track(){}
	track(const track &rhs) = default;
	track(track &&rhs) noexcept = default;
	track& operator=(const track &rhs) = default;
	track& operator=(track &&rhs) noexcept = default;

	platform::string_t duration;
	platform::string_t position;
	platform::string_t type_;
	platform::string_t title;
	std::vector<artist> artists;
	std::vector<artist> extraartists;
};


class note {
public:
	note():field_id(0){}
	~note(){}
	note(const note &rhs) = default;
	note(note &&rhs) noexcept = default;
	note& operator=(const note &rhs) = default;
	note& operator=(note &&rhs) noexcept = default;

	int field_id;
	platform::string_t value;
};


class format {
public:
	format(){}
	~format(){}
	format(const format &rhs) = default;
	format(format &&rhs) noexcept = default;
	format& operator=(const format &rhs) = default;
	format& operator=(format &&rhs) noexcept = default;

	platform::string_t name;
	platform::string_t qty;
	platform::string_t text;
	std::vector<platform::string_t> descriptions;
};


class series {
public:
	series():id(0){}
	~series(){}
	series(const series &rhs) = default;
	series(series &&rhs) noexcept = default;
	series& operator=(const series &rhs) = default;
	series& operator=(series &&rhs) noexcept = default;

	int id;
	platform::string_t name;
	platform::string_t entity_type;
	platform::string_t catno;
	platform::string_t resource_url;
	platform::string_t entity_type_name;
};


class community {
public:
	community():want(0),have(0){}
	~community(){}
	community(const community &rhs) = default;
	community(community &&rhs) noexcept = default;
	community& operator=(const community &rhs) = default;
	community& operator=(community &&rhs) noexcept = default;

	int want;
	int have;
	platform::string_t status;
	platform::string_t data_quality;
	submitter sumbitter_;
	rating rating_;
	std::vector<contributor> contributors;
};


class basic_information {
public:
	basic_information():id(0),master_id(0),year(0){}
	~basic_information(){}
	basic_information(const basic_information &rhs) = default;
	basic_information(basic_information &&rhs) noexcept = default;
	basic_information& operator=(const basic_information &rhs) = default;
	basic_information& operator=(basic_information &&rhs) noexcept = default;

	int id;
	int master_id;
	int year;
	platform::string_t thumb;
	platform::string_t title;
	platform::string_t cover_image;
	platform::string_t resource_url;
	platform::string_t master_url;
	std::vector<label> labels;
	std::vector<format> formats;
	std::vector<artist> artists;
	std::vector<note> notes;
};


class want {
public:
	want():rating(0),id(0){}
	~want(){}
	want(const want &rhs) = default;
	want(want &&rhs) noexcept = default;
	want& operator=(const want &rhs) = default;
	want& operator=(want &&rhs) noexcept = default;

	int rating;
	int id;
	platform::string_t resource_url;
	platform::string_t date_added;
	platform::string_t notes;
	basic_information basic_information_;
};

} // namespace discogs
} // namespace parser
} // namespace common
