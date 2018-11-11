/* clang-format off */
#pragma once
#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>

#include "wantlist.hpp"


#include "parser_common.hpp"

namespace discogs {
namespace parser {

enum class StateKey;

class wantlist_parser : public rapidjson::BaseReaderHandler<rjs_UTF_t, wantlist_parser> {
public:
	wantlist_parser();
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
	wantlist wantlist_;
};

} // namespace discogs
} // namespace parser
