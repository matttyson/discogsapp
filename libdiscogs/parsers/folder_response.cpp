/* clang-format off */
#include "folder_response_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	folder_response,
	folder_response_id,
	folder_response_count,
	folder_response_name,
	folder_response_resource_url,
};

bool folder_response_parser::Int(int value)
{
    return Number((int)value);
}

bool folder_response_parser::Uint(unsigned int value)
{
    return Number((int)value);
}

bool folder_response_parser::Int64(int64_t i)
{
    return false;
}

bool folder_response_parser::Uint64(uint64_t i)
{
    return false;
}

bool folder_response_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool folder_response_parser::Number(int value)
{
	switch(m_state){
	case StateKey::folder_response_id:
		folder_response.id = value;
		m_state = StateKey::folder_response;
		break;
	case StateKey::folder_response_count:
		folder_response.count = value;
		m_state = StateKey::folder_response;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_response_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_response_name:
		folder_response.name = ::platform::string_t(value, length);
		m_state = StateKey::folder_response;
		break;
	case StateKey::folder_response_resource_url:
		folder_response.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::folder_response;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_response_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool folder_response_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool folder_response_parser::Null()
{
	switch(m_state){
		case StateKey::folder_response_id:
			m_state = StateKey::folder_response;
			break;
		case StateKey::folder_response_count:
			m_state = StateKey::folder_response;
			break;
		case StateKey::folder_response_name:
			m_state = StateKey::folder_response;
			break;
		case StateKey::folder_response_resource_url:
			m_state = StateKey::folder_response;
			break;
	}
	return true;
}
bool folder_response_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_response:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_response_id;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("count")) == 0){
			m_state = StateKey::folder_response_count;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_response_name;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_response_resource_url;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool folder_response_parser::StartArray()
{
	return true;
}
bool folder_response_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

bool folder_response_parser::StartObject()
{
	switch(m_state){
	}
	return true;
}

bool folder_response_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

folder_response_parser::folder_response_parser()
{
	m_state = StateKey::folder_response;
}

} // namespace discogs
} // namespace parser
