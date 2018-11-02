#include "config.hpp"

#include <tuple>
#include <map>

#include "libplatform/file.hpp"
#include "libplatform/rapidjson_file.hpp"

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
	element(const platform::string_t &str)
		:strval(str), intval(0), type(element_type::string_type)
	{}
	element(const platform::char_t *str, int length)
		:strval(str, length), intval(0), type(element_type::string_type)
	{}
	element()
		:type(element_type::none_type)
	{}

	platform::string_t strval;
	int intval;
	element_type type;
};

class config_private {
public:
	config_private(const platform::string_t &filename_)
		:filename(filename_)
	{}

	platform::string_t filename;
	std::map<platform::string_t, element> data;
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
	platform::string_t current_key;
	std::map<platform::string_t, element> data;
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
	current_key = ::platform::string_t(str, length);
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

config::config(const platform::string_t &filename)
	:m_data(new config_private(filename))
{
}

config::~config()
{
}


bool config::read()
{
	char buffer[512];
	config_parser p;
	platform::file f;

	const bool rc = f.open(
		m_data->filename,
		platform::file::io_mode::read,
		platform::file::create_mode::open
	);

	if(!rc){
		return false;
	}

	platform::PlatformReadStream frs{f, buffer, sizeof(buffer)};
	platform::Reader r;

	rapidjson::ParseResult pr = r.Parse(frs, p);

	if(pr.IsError()){
		return false;
	}

	m_data->data = std::move(p.data);
	return true;
}

bool config::write()
{
	char buffer[512];
	platform::file f;

	const bool rc = f.open(
		m_data->filename,
		platform::file::io_mode::write,
		platform::file::create_mode::trunc
	);

	if(!rc){
		return false;
	}

	platform::PlatformWriteStream pws{f, buffer, sizeof(buffer)};
	platform::PrettyFileWriter pfw{pws};

	pfw.SetIndent('\t', 1);

	pfw.StartObject();

	for(const auto &kv : m_data->data){
		pfw.Key(kv.first.c_str(), kv.first.length());
		switch(kv.second.type){
		case element_type::string_type:
			pfw.String(kv.second.strval.c_str());
			break;
		case element_type::int_type:
			pfw.Int(kv.second.intval);
			break;
		}
	}

	pfw.EndObject();

	return true;
}

bool config::get(const platform::string_t &key, platform::string_t &value)
{
	if(m_data->data.find(key) == m_data->data.end()){
		return false;
	}

	const auto &temp = m_data->data[key];
	value = temp.strval;

	return true;
}

bool config::get(const platform::string_t &key, int &value)
{
	if (m_data->data.find(key) == m_data->data.end()) {
		return false;
	}

	const auto &temp = m_data->data[key];
	value = temp.intval;

	return true;
}

void config::set(const platform::string_t &key, const platform::string_t &value)
{
	m_data->data[key] = value;
}

void config::set(const platform::string_t &key, int value)
{
	m_data->data[key] = value;
}

void config::remove(const platform::string_t &key)
{
	m_data->data.erase(key);
}

}
