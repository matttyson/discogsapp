#pragma once
#include "class_common.hpp"

// Classes that can be reused in most endpoints

namespace discogs {
namespace parser {
namespace common {

class contributor {
public:
	contributor(){}
	contributor
		(string_t &&username__, string_t &&resource_url__) noexcept
		:username(username__), resource_url(resource_url__) {}
	~contributor(){}
	contributor(const contributor &rhs) = default;
	contributor(contributor &&rhs) noexcept = default;
	contributor& operator=(const contributor &rhs) = default;
	contributor& operator=(contributor &&rhs) noexcept = default;

	string_t username;
	string_t resource_url;
};


class identifier {
public:
	identifier(){}
	identifier
		(string_t &&type__, string_t &&value__, string_t &&description__) noexcept
		:type(type__), value(value__), description(description__) {}
	~identifier(){}
	identifier(const identifier &rhs) = default;
	identifier(identifier &&rhs) noexcept = default;
	identifier& operator=(const identifier &rhs) = default;
	identifier& operator=(identifier &&rhs) noexcept = default;

	string_t type;
	string_t value;
	string_t description;
};


class label {
public:
	label():id(0){}
	label
		(int id__, string_t &&name__, string_t &&entity_type__, string_t &&catno__, string_t &&resource_url__, string_t &&entity_type_name__) noexcept
		:id(id__), name(name__), entity_type(entity_type__), catno(catno__), resource_url(resource_url__), entity_type_name(entity_type_name__) {}
	~label(){}
	label(const label &rhs) = default;
	label(label &&rhs) noexcept = default;
	label& operator=(const label &rhs) = default;
	label& operator=(label &&rhs) noexcept = default;

	int id;
	string_t name;
	string_t entity_type;
	string_t catno;
	string_t resource_url;
	string_t entity_type_name;
};


class video {
public:
	video():duration(0),embed(false){}
	video
		(int duration__, bool embed__, string_t &&description__, string_t &&title__, string_t &&uri__) noexcept
		:duration(duration__), embed(embed__), description(description__), title(title__), uri(uri__) {}
	~video(){}
	video(const video &rhs) = default;
	video(video &&rhs) noexcept = default;
	video& operator=(const video &rhs) = default;
	video& operator=(video &&rhs) noexcept = default;

	int duration;
	bool embed;
	string_t description;
	string_t title;
	string_t uri;
};


class company {
public:
	company():id(0){}
	company
		(int id__, string_t &&name__, string_t &&entity_type__, string_t &&catno__, string_t &&resource_url__, string_t &&entity_type_name__) noexcept
		:id(id__), name(name__), entity_type(entity_type__), catno(catno__), resource_url(resource_url__), entity_type_name(entity_type_name__) {}
	~company(){}
	company(const company &rhs) = default;
	company(company &&rhs) noexcept = default;
	company& operator=(const company &rhs) = default;
	company& operator=(company &&rhs) noexcept = default;

	int id;
	string_t name;
	string_t entity_type;
	string_t catno;
	string_t resource_url;
	string_t entity_type_name;
};


class rating {
public:
	rating():count(0),average(0.0){}
	rating
		(int count__, double average__) noexcept
		:count(count__), average(average__) {}
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
	submitter
		(string_t &&username__, string_t &&resource_url__) noexcept
		:username(username__), resource_url(resource_url__) {}
	~submitter(){}
	submitter(const submitter &rhs) = default;
	submitter(submitter &&rhs) noexcept = default;
	submitter& operator=(const submitter &rhs) = default;
	submitter& operator=(submitter &&rhs) noexcept = default;

	string_t username;
	string_t resource_url;
};


class artist {
public:
	artist():id(0){}
	artist
		(int id__, string_t &&join__, string_t &&name__, string_t &&anv__, string_t &&tracks__, string_t &&role__, string_t &&resource_url__) noexcept
		:id(id__), join(join__), name(name__), anv(anv__), tracks(tracks__), role(role__), resource_url(resource_url__) {}
	~artist(){}
	artist(const artist &rhs) = default;
	artist(artist &&rhs) noexcept = default;
	artist& operator=(const artist &rhs) = default;
	artist& operator=(artist &&rhs) noexcept = default;

	int id;
	string_t join;
	string_t name;
	string_t anv;
	string_t tracks;
	string_t role;
	string_t resource_url;
};


class image {
public:
	image():height(0),width(0){}
	image
		(int height__, int width__, string_t &&uri__, string_t &&resource_url__, string_t &&type__, string_t &&uri150__) noexcept
		:height(height__), width(width__), uri(uri__), resource_url(resource_url__), type(type__), uri150(uri150__) {}
	~image(){}
	image(const image &rhs) = default;
	image(image &&rhs) noexcept = default;
	image& operator=(const image &rhs) = default;
	image& operator=(image &&rhs) noexcept = default;

	int height;
	int width;
	string_t uri;
	string_t resource_url;
	string_t type;
	string_t uri150;
};


class track {
public:
	track(){}
	track
		(string_t &&duration__, string_t &&position__, string_t &&type___, string_t &&title__) noexcept
		:duration(duration__), position(position__), type_(type___), title(title__) {}
	~track(){}
	track(const track &rhs) = default;
	track(track &&rhs) noexcept = default;
	track& operator=(const track &rhs) = default;
	track& operator=(track &&rhs) noexcept = default;

	string_t duration;
	string_t position;
	string_t type_;
	string_t title;
};


class note {
public:
	note():field_id(0){}
	note
		(int field_id__, string_t &&value__) noexcept
		:field_id(field_id__), value(value__) {}
	~note(){}
	note(const note &rhs) = default;
	note(note &&rhs) noexcept = default;
	note& operator=(const note &rhs) = default;
	note& operator=(note &&rhs) noexcept = default;

	int field_id;
	string_t value;
};


class format {
public:
	format(){}
	format
		(string_t &&name__, string_t &&qty__, string_t &&text__, std::vector<string_t> &&descriptions__) noexcept
		:name(name__), qty(qty__), text(text__), descriptions(descriptions__) {}
	~format(){}
	format(const format &rhs) = default;
	format(format &&rhs) noexcept = default;
	format& operator=(const format &rhs) = default;
	format& operator=(format &&rhs) noexcept = default;

	string_t name;
	string_t qty;
	string_t text;
	std::vector<string_t> descriptions;
};


class community {
public:
	community():want(0),have(0){}
	community
		(int want__, int have__, string_t &&status__, string_t &&data_quality__, submitter &&sumbitter___, rating &&rating___, std::vector<contributor> &&contributors__) noexcept
		:want(want__), have(have__), status(status__), data_quality(data_quality__), sumbitter_(sumbitter___), rating_(rating___), contributors(contributors__) {}
	~community(){}
	community(const community &rhs) = default;
	community(community &&rhs) noexcept = default;
	community& operator=(const community &rhs) = default;
	community& operator=(community &&rhs) noexcept = default;

	int want;
	int have;
	string_t status;
	string_t data_quality;
	submitter sumbitter_;
	rating rating_;
	std::vector<contributor> contributors;
};


class basic_information {
public:
	basic_information():id(0),master_id(0),year(0){}
	basic_information
		(int id__, int master_id__, int year__, string_t &&thumb__, string_t &&title__, string_t &&cover_image__, string_t &&resource_url__, string_t &&master_url__, std::vector<label> &&labels__, std::vector<format> &&formats__, std::vector<artist> &&artists__, std::vector<note> &&notes__) noexcept
		:id(id__), master_id(master_id__), year(year__), thumb(thumb__), title(title__), cover_image(cover_image__), resource_url(resource_url__), master_url(master_url__), labels(labels__), formats(formats__), artists(artists__), notes(notes__) {}
	~basic_information(){}
	basic_information(const basic_information &rhs) = default;
	basic_information(basic_information &&rhs) noexcept = default;
	basic_information& operator=(const basic_information &rhs) = default;
	basic_information& operator=(basic_information &&rhs) noexcept = default;

	int id;
	int master_id;
	int year;
	string_t thumb;
	string_t title;
	string_t cover_image;
	string_t resource_url;
	string_t master_url;
	std::vector<label> labels;
	std::vector<format> formats;
	std::vector<artist> artists;
	std::vector<note> notes;
};


class want {
public:
	want():rating(0),id(0){}
	want
		(int rating__, int id__, string_t &&resource_url__, string_t &&date_added__, basic_information &&basic_information___) noexcept
		:rating(rating__), id(id__), resource_url(resource_url__), date_added(date_added__), basic_information_(basic_information___) {}
	~want(){}
	want(const want &rhs) = default;
	want(want &&rhs) noexcept = default;
	want& operator=(const want &rhs) = default;
	want& operator=(want &&rhs) noexcept = default;

	int rating;
	int id;
	string_t resource_url;
	string_t date_added;
	basic_information basic_information_;
};

} // namespace discogs
} // namespace parser
} // namespace common
