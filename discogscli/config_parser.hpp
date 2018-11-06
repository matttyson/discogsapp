#pragma once

#include "rapidjson/reader.h"
#include "libplatform/platform.hpp"

namespace {

struct element {
	enum class type {
		string_type,
		int_type,
		none_type
	};

	element(int i)
		:strval(STR("")), intval(i), type_(type::int_type)
	{}
	element(const platform::string_t &str)
		:strval(str), intval(0), type_(type::string_type)
	{}
	element(const platform::char_t *str, int length)
		:strval(str, length), intval(0), type_(type::string_type)
	{}
	element()
		:type_(type::none_type)
	{}

	platform::string_t strval;
	int intval;
	type type_;
};

class config_parser : public rapidjson::BaseReaderHandler<rjs_UTF_t, config_parser> {
public:
	bool Null() {
		return false;
	}
	bool Bool(bool b) {
		return false;
	}
	bool Int(int value) {
		data.emplace(current_key, (int)value);
		return true;
	}
	bool Uint(unsigned int value) {
		data.emplace(current_key, (int)value);
		return true;
	}
	bool Int64(int64_t value) {
		return false;
	}
	bool Uint64(uint64_t value) {
		return false;
	}
	bool Double(double value) {
		return false;
	}
	bool String(const Ch* str, rapidjson::SizeType length, bool copy) {
		data.emplace(current_key, element(str, length));
		return true;
	}
	bool Key(const Ch* str, rapidjson::SizeType length, bool copy) {
		current_key = ::platform::string_t(str, length);
		return true;
	}
	bool StartObject() {
		return true;
	}
	bool EndObject(rapidjson::SizeType memberCount) {
		return true;
	}
	bool StartArray() {
		return true;
	}
	bool EndArray(rapidjson::SizeType elementCount) {
		return true;
	}
public:
	platform::string_t current_key;
	std::map<platform::string_t, element> data;
};

}
