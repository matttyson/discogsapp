/* clang-format off */
#include "collection_add_response_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	collection_add_response,
	collection_add_response_instance_id,
	collection_add_response_resource_url,
};

bool collection_add_response_parser::Int(int value)
{
	return Number((int)value);
}

bool collection_add_response_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool collection_add_response_parser::Int64(int64_t i)
{
	return false;
}

bool collection_add_response_parser::Uint64(uint64_t i)
{
	return false;
}

bool collection_add_response_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool collection_add_response_parser::Number(int value)
{
	switch(m_state){
	case StateKey::collection_add_response_instance_id:
		RESULT.instance_id = value;
		m_state = StateKey::collection_add_response;
		break;
	default:
		return false;
	}
	return true;
}
bool collection_add_response_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::collection_add_response_resource_url:
		RESULT.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::collection_add_response;
		break;
	default:
		return false;
	}
	return true;
}
bool collection_add_response_parser::Bool(bool value)
{
	return false;
}
bool collection_add_response_parser::Double(double value)
{
	return false;
}
bool collection_add_response_parser::Null()
{
	switch(m_state){
		case StateKey::collection_add_response_instance_id:
			m_state = StateKey::collection_add_response;
			break;
		case StateKey::collection_add_response_resource_url:
			m_state = StateKey::collection_add_response;
			break;
	}
	return true;
}
bool collection_add_response_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::collection_add_response:
		if(length == 11 && platform::strcmp(str, STR("instance_id")) == 0){
			m_state = StateKey::collection_add_response_instance_id;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::collection_add_response_resource_url;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool collection_add_response_parser::StartArray()
{
	return true;
}
bool collection_add_response_parser::EndArray(rapidjson::SizeType memberCount)
{
	return true;
}

bool collection_add_response_parser::StartObject()
{
	return true;
}

bool collection_add_response_parser::EndObject(rapidjson::SizeType memberCount)
{
	return true;
}

collection_add_response_parser::collection_add_response_parser()
{
	m_state = StateKey::collection_add_response;
}

} // namespace discogs
} // namespace parser
