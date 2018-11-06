#include "config.hpp"

#include <tuple>
#include <map>

#include "libplatform/file.hpp"
#include "libplatform/rapidjson_file.hpp"

#include "config_parser.hpp"

namespace discogs {

class config_private {
public:
	config_private(const platform::string_t &filename_)
		:filename(filename_)
	{}

	platform::string_t filename;
	std::map<platform::string_t, element> data;
};



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
		switch(kv.second.type_){
		case element::type::string_type:
			pfw.String(kv.second.strval.c_str());
			break;
		case element::type::int_type:
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
