#include "config.hpp"

#include <tuple>
#include <map>

#include <rapidjson/rapidjson.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>

#ifdef DISCOGS_WCHAR
typedef rapidjson::UTF16<> rjs_UTF_t;
#else
typedef rapidjson::UTF8<> rjs_UTF_t;
#endif


// This code is really shitty. I need to fix it later.

namespace discogs {

enum class element_type {
	string_type,
	int_type,
	none_type
};

struct element {

	element(int i)
		:strval(STR("")), intval(i), type(element_type::int_type)
	{}
	element(const string_t &str)
		:strval(str), intval(0), type(element_type::string_type)
	{}
	element(const char_t *str, int length)
		:strval(str, length), intval(0), type(element_type::string_type)
	{}
	element()
		:type(element_type::none_type)
	{}

	discogs::string_t strval;
	int intval;
	element_type type;
};

class config_private {
public:
	config_private(const discogs::string_t filename_)
		:filename(filename_)
	{}

	string_t filename;
	std::map<string_t, element> data;
};


class config_parser : public rapidjson::BaseReaderHandler<rjs_UTF_t, config_parser> {
public:
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
public:
	discogs::string_t current_key;
	std::map<string_t, element> data;
};

bool config_parser::Null()
{
	return false;
}

bool config_parser::Bool(bool b)
{
	return false;
}
bool config_parser::Int(int value)
{
	data.emplace(current_key, (int)value);
	return true;
}
bool config_parser::Uint(unsigned int value)
{
	data.emplace(current_key, (int)value);
	return true;
}
bool config_parser::Int64(int64_t value)
{
	return false;
}
bool config_parser::Uint64(uint64_t value)
{
	return false;
}
bool config_parser::Double(double value)
{
	return false;
}
bool config_parser::String(const Ch* str, rapidjson::SizeType length, bool copy)
{
	data.emplace(current_key, element(str, length));
	return true;
}
bool config_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	current_key = string_t(str, length);
	return true;
}
bool config_parser::StartObject()
{
	return true;
}
bool config_parser::EndObject(rapidjson::SizeType memberCount)
{
	return true;
}
bool config_parser::StartArray()
{
	return false;
}
bool config_parser::EndArray(rapidjson::SizeType memberCount)
{
	return false;
}

config::config(const discogs::string_t &filename)
	:m_data(new config_private(filename))
{
}

config::~config()
{
}

bool config::read()
{
	char buffer[512];
	FILE *fp;
	config_parser p;

#ifdef DISCOGS_WCHAR
	fp = _wfopen(m_data->filename.c_str(), L"r");
#else
	fp = fopen(m_data->filename.c_str(), "r");
#endif
	if(fp == NULL){
		return 0;
	}
	rapidjson::FileReadStream frs(fp, buffer, sizeof(buffer));

	// Reading from UTF-8 into whatever.
	rapidjson::GenericReader<rapidjson::UTF8<>, rjs_UTF_t> r;

	rapidjson::ParseResult pr = r.Parse(frs, p);

	fclose(fp);

	if(pr.IsError()){
		return false;
	}

	m_data->data = std::move(p.data);

	return true;
}

bool config::write()
{
	char buffer[512];
	FILE *fp;

#ifdef DISCOGS_WCHAR
	fp = _wfopen(m_data->filename.c_str(), L"w");
#else
	fp = fopen(m_data->filename.c_str(), "w");
#endif

	if(fp == NULL){
		return false;
	}

	rapidjson::FileWriteStream fws(fp, buffer, sizeof(buffer));
	rapidjson::PrettyWriter<rapidjson::FileWriteStream, rjs_UTF_t, rapidjson::UTF8<> > pw(fws);

	pw.SetIndent('\t', 1);

	pw.StartObject();

	for(const auto &kv : m_data->data){
		pw.Key(kv.first.c_str(), kv.first.length());
		switch(kv.second.type){
		case element_type::string_type:
			pw.String(kv.second.strval.c_str());
			break;
		case element_type::int_type:
			pw.Int(kv.second.intval);
			break;
		}
	}

	pw.EndObject();
	fws.Flush();

	fclose(fp);

	return true;
}

bool config::get(const discogs::string_t &key, discogs::string_t &value)
{
	if(m_data->data.find(key) == m_data->data.end()){
		return false;
	}

	const auto &temp = m_data->data[key];
	value = temp.strval;

	return true;
}

bool config::get(const discogs::string_t &key, int &value)
{
	if (m_data->data.find(key) == m_data->data.end()) {
		return false;
	}

	const auto &temp = m_data->data[key];
	value = temp.intval;

	return true;
}

void config::set(const discogs::string_t &key, const discogs::string_t &value)
{
	m_data->data[key] = value;
}

void config::set(const discogs::string_t &key, int value)
{
	m_data->data[key] = value;
}

}
