#pragma once
#include "class_common.hpp"

// basic_information template class

namespace discogs {
namespace parser {
namespace common {

class note {
public:
	note() :field_id(0) {}
	~note() {}
	note(const note &rhs) = default;
	note(note &&rhs) noexcept = default;
	note& operator=(const note &rhs) = default;
	note& operator=(note &&rhs) noexcept = default;

	int field_id;
	string_t value;
};


class basic_information {
public:
	basic_information() :id(0), master_id(0), year(0), folder_id(0) {}
	~basic_information() {}
	basic_information(const basic_information &rhs) = default;
	basic_information(basic_information &&rhs) noexcept = default;
	basic_information& operator=(const basic_information &rhs) = default;
	basic_information& operator=(basic_information &&rhs) noexcept = default;

	int id;
	int master_id;
	int year;
	int folder_id;
	string_t thumb;
	string_t name;
	string_t title;
	string_t cover_image;
	string_t resource_url;
	string_t master_url;
	std::vector<label> label_;
	std::vector<format> format_;
	std::vector<artist> artist_;
	std::vector<note> notes_;
};

} // namespace discogs
} // namespace parser
} // namespace common
