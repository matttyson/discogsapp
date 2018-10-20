/* clang-format off */
#include "../private_include/collection_parser.hpp"
#include "porting.h"

namespace discogs {
namespace parser {
namespace collection {

template <typename T>
static inline int my_strcmp(const T *str1, const T *str2)
{
	if constexpr (sizeof(T) == sizeof(char)) {
		return ::strcmp(str1, str2);
	}
	else if constexpr (sizeof(T) == sizeof(wchar_t)) {
		return ::wcscmp(str1, str2);
	}
}

enum class StateKey {
	folder,
	folder_id,
	folder_count,
	folder_resource_url,
	folder_name,
};

bool super_parser::Null()
{
    return false;
}

bool super_parser::StartObject()
{
    return true;
}

bool super_parser::Int(int value)
{
    return Number((int)value);
}

bool super_parser::Uint(unsigned int value)
{
    return Number((int)value);
}

bool super_parser::Int64(int64_t i)
{
    return false;
}

bool super_parser::Uint64(uint64_t i)
{
    return false;
}

bool super_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool super_parser::Number(int value)
{
	switch(m_state){
	case StateKey::folder_id:
		folders.back().id = value;
		m_state = StateKey::folder;
		break;
	case StateKey::folder_count:
		folders.back().count = value;
		m_state = StateKey::folder;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_resource_url:
		folders.back().resource_url = std::string(value, length);
		m_state = StateKey::folder;
		break;
	case StateKey::folder_name:
		folders.back().name = std::string(value, length);
		m_state = StateKey::folder;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool super_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool super_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder:
		if(length == 2 && my_strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_id;
		}
		else
		if(length == 5 && my_strcmp(str, STR("count")) == 0){
			m_state = StateKey::folder_count;
		}
		else
		if(length == 12 && my_strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_resource_url;
		}
		else
		if(length == 4 && my_strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_name;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool super_parser::StartArray()
{
	switch(m_state){
	}
	return true;
}

bool super_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

bool super_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	}
	return true;
}

super_parser::super_parser()
{
	m_state = StateKey::folder;
}

} // namespace discogs
} // namespace parser
} // namespace collection
