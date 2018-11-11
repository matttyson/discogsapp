/* clang-format off */
#pragma once
#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>

#include "folder_releases.hpp"


#include "parser_common.hpp"

namespace discogs {
namespace parser {

enum class StateKey;

class folder_releases_parser : public rapidjson::BaseReaderHandler<rjs_UTF_t, folder_releases_parser> {
public:
	folder_releases_parser();
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
	bool Number(int value);
	StateKey m_state;
	folder_releases RESULT;
};

} // namespace discogs
} // namespace parser
