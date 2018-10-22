/* clang-format off */
#include "collection_parser.hpp"
#include "porting.h"
namespace discogs {
namespace parser {
namespace collection {

enum class StateKey {
	folder_list,
	folder_list_folders,
	folder_list_folders_id,
	folder_list_folders_count,
	folder_list_folders_resource_url,
	folder_list_folders_name,
};

bool state_parser::Int(int value)
{
    return Number((int)value);
}

bool state_parser::Uint(unsigned int value)
{
    return Number((int)value);
}

bool state_parser::Int64(int64_t i)
{
    return false;
}

bool state_parser::Uint64(uint64_t i)
{
    return false;
}

bool state_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool state_parser::Number(int value)
{
	switch(m_state){
	case StateKey::folder_list_folders_id:
		folder_list_.folders.back().id = value;
		m_state = StateKey::folder_list_folders;
		break;
	case StateKey::folder_list_folders_count:
		folder_list_.folders.back().count = value;
		m_state = StateKey::folder_list_folders;
		break;
	default:
		return false;
	}
	return true;
}
bool state_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_list_folders_resource_url:
		folder_list_.folders.back().resource_url = string_t(value, length);
		m_state = StateKey::folder_list_folders;
		break;
	case StateKey::folder_list_folders_name:
		folder_list_.folders.back().name = string_t(value, length);
		m_state = StateKey::folder_list_folders;
		break;
	default:
		return false;
	}
	return true;
}
bool state_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool state_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool state_parser::Null()
{
	switch(m_state){
		case StateKey::folder_list_folders:
			m_state = StateKey::folder_list;
			break;
		case StateKey::folder_list_folders_id:
			m_state = StateKey::folder_list_folders;
			break;
		case StateKey::folder_list_folders_count:
			m_state = StateKey::folder_list_folders;
			break;
		case StateKey::folder_list_folders_resource_url:
			m_state = StateKey::folder_list_folders;
			break;
		case StateKey::folder_list_folders_name:
			m_state = StateKey::folder_list_folders;
			break;
	}
	return true;
}
bool state_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_list_folders:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_list_folders_id;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("count")) == 0){
			m_state = StateKey::folder_list_folders_count;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_list_folders_resource_url;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_list_folders_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_list:
		if(length == 7 && discogs::strcmp(str, STR("folders")) == 0){
			m_state = StateKey::folder_list_folders;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool state_parser::StartArray()
{
	return true;
}
bool state_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::folder_list_folders:
		m_state = StateKey::folder_list;
		break;
	}
	return true;
}

bool state_parser::StartObject()
{
	switch(m_state){
	case StateKey::folder_list_folders:
		folder_list_.folders.emplace_back();
		break;
	}
	return true;
}

bool state_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

state_parser::state_parser()
{
	m_state = StateKey::folder_list;
}

} // namespace discogs
} // namespace parser
} // namespace collection