/* clang-format off */
#include "identity_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	identity,
	identity_id,
	identity_username,
	identity_resource_url,
	identity_consumer_name,
	identity_message,
};

bool identity_parser::Int(int value)
{
    return Number((int)value);
}

bool identity_parser::Uint(unsigned int value)
{
    return Number((int)value);
}

bool identity_parser::Int64(int64_t i)
{
    return false;
}

bool identity_parser::Uint64(uint64_t i)
{
    return false;
}

bool identity_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool identity_parser::Number(int value)
{
	switch(m_state){
	case StateKey::identity_id:
		identity_.id = value;
		m_state = StateKey::identity;
		break;
	default:
		return false;
	}
	return true;
}
bool identity_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::identity_username:
		identity_.username = ::platform::string_t(value, length);
		m_state = StateKey::identity;
		break;
	case StateKey::identity_resource_url:
		identity_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::identity;
		break;
	case StateKey::identity_consumer_name:
		identity_.consumer_name = ::platform::string_t(value, length);
		m_state = StateKey::identity;
		break;
	case StateKey::identity_message:
		identity_.message = ::platform::string_t(value, length);
		m_state = StateKey::identity;
		break;
	default:
		return false;
	}
	return true;
}
bool identity_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool identity_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool identity_parser::Null()
{
	switch(m_state){
		case StateKey::identity_id:
			m_state = StateKey::identity;
			break;
		case StateKey::identity_username:
			m_state = StateKey::identity;
			break;
		case StateKey::identity_resource_url:
			m_state = StateKey::identity;
			break;
		case StateKey::identity_consumer_name:
			m_state = StateKey::identity;
			break;
		case StateKey::identity_message:
			m_state = StateKey::identity;
			break;
	}
	return true;
}
bool identity_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::identity:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::identity_id;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("username")) == 0){
			m_state = StateKey::identity_username;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::identity_resource_url;
		}
		else
		if(length == 13 && platform::strcmp(str, STR("consumer_name")) == 0){
			m_state = StateKey::identity_consumer_name;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("message")) == 0){
			m_state = StateKey::identity_message;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool identity_parser::StartArray()
{
	return true;
}
bool identity_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

bool identity_parser::StartObject()
{
	switch(m_state){
	}
	return true;
}

bool identity_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

identity_parser::identity_parser()
{
	m_state = StateKey::identity;
}

} // namespace discogs
} // namespace parser
