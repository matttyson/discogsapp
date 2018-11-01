#pragma once


#include <rapidjson/reader.h>
#include "platform_rjs.hpp"

enum class StateKey;

class rapidjson_test_parser : public rapidjson::BaseReaderHandler<rjs_UTF_t, rapidjson_test_parser> {
public:
	rapidjson_test_parser();
	bool Null();
	bool Bool(bool b);
	bool Int(int value);
	bool Uint(unsigned int value);
	bool Int64(int64_t value);
	bool Uint64(uint64_t value);
	bool Double(double value);
	bool String(const Ch* str, rapidjson::SizeType length, bool copy);
	bool Key(const Ch* str, rapidjson::SizeType length, bool copy);
	bool StartObject();
	bool EndObject(rapidjson::SizeType memberCount);
	bool StartArray();
	bool EndArray(rapidjson::SizeType elementCount);
	bool RawNumber(const Ch * str, rapidjson::SizeType length, bool copy);
public:
};

rapidjson_test_parser::rapidjson_test_parser()
{
}

bool rapidjson_test_parser::Null()
{
	return true;
}

bool rapidjson_test_parser::Bool(bool b)
{
	return true;
}

bool rapidjson_test_parser::Int(int value)
{
	return true;
}

bool rapidjson_test_parser::Uint(unsigned int value)
{
	return true;
}

bool rapidjson_test_parser::Int64(int64_t value)
{
	return true;
}

bool rapidjson_test_parser::Uint64(uint64_t value)
{
	return true;
}

bool rapidjson_test_parser::Double(double value)
{
	return true;
}

bool rapidjson_test_parser::String(const Ch* str, rapidjson::SizeType length, bool copy)
{
	return true;
}

bool rapidjson_test_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	return true;
}

bool rapidjson_test_parser::StartObject()
{
	return true;
}

bool rapidjson_test_parser::EndObject(rapidjson::SizeType memberCount)
{
	return true;
}

bool rapidjson_test_parser::StartArray()
{
	return true;
}

bool rapidjson_test_parser::EndArray(rapidjson::SizeType memberCount)
{
	return true;
}

bool rapidjson_test_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return true;
}
