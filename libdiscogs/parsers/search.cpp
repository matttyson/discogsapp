/* clang-format off */
#include "search_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace result {

enum class StateKey {
	search_results,
	search_results_pagination,
	search_results_pagination_per_page,
	search_results_pagination_items,
	search_results_pagination_page,
	search_results_pagination_pages,
	search_results_pagination_urls,
	search_results_pagination_urls_next,
	search_results_pagination_urls_last,
	search_results_pagination_urls_first,
	search_results_pagination_urls_prev,
	search_results_results,
	search_results_results_id,
	search_results_results_master_id,
	search_results_results_thumb,
	search_results_results_title,
	search_results_results_country,
	search_results_results_resource_url,
	search_results_results_type,
	search_results_results_uri,
	search_results_results_catno,
	search_results_results_year,
	search_results_results_cover_image,
	search_results_results_master_url,
	search_results_results_barcode,
	search_results_results_format,
	search_results_results_label,
	search_results_results_style,
	search_results_results_genre,
	search_results_results_community,
	search_results_results_community_have,
	search_results_results_community_want,
	search_results_results_user_data,
	search_results_results_user_data_in_collection,
	search_results_results_user_data_in_wantlist,
};

bool search_parser::Int(int value)
{
	return Number((int)value);
}

bool search_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool search_parser::Int64(int64_t i)
{
	return false;
}

bool search_parser::Uint64(uint64_t i)
{
	return false;
}

bool search_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool search_parser::Number(int value)
{
	switch(m_state){
	case StateKey::search_results_pagination_per_page:
		RESULT.pages.per_page = value;
		m_state = StateKey::search_results_pagination;
		break;
	case StateKey::search_results_pagination_items:
		RESULT.pages.items = value;
		m_state = StateKey::search_results_pagination;
		break;
	case StateKey::search_results_pagination_page:
		RESULT.pages.page = value;
		m_state = StateKey::search_results_pagination;
		break;
	case StateKey::search_results_pagination_pages:
		RESULT.pages.pages = value;
		m_state = StateKey::search_results_pagination;
		break;
	case StateKey::search_results_results_id:
		RESULT.results.back().id = value;
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_master_id:
		RESULT.results.back().master_id = value;
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_community_have:
		RESULT.results.back().community.have = value;
		m_state = StateKey::search_results_results_community;
		break;
	case StateKey::search_results_results_community_want:
		RESULT.results.back().community.want = value;
		m_state = StateKey::search_results_results_community;
		break;
	default:
		return false;
	}
	return true;
}
bool search_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::search_results_pagination_urls_next:
		RESULT.pages.links.next = ::platform::string_t(value, length);
		m_state = StateKey::search_results_pagination_urls;
		break;
	case StateKey::search_results_pagination_urls_last:
		RESULT.pages.links.last = ::platform::string_t(value, length);
		m_state = StateKey::search_results_pagination_urls;
		break;
	case StateKey::search_results_pagination_urls_first:
		RESULT.pages.links.first = ::platform::string_t(value, length);
		m_state = StateKey::search_results_pagination_urls;
		break;
	case StateKey::search_results_pagination_urls_prev:
		RESULT.pages.links.prev = ::platform::string_t(value, length);
		m_state = StateKey::search_results_pagination_urls;
		break;
	case StateKey::search_results_results_thumb:
		RESULT.results.back().thumb = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_title:
		RESULT.results.back().title = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_country:
		RESULT.results.back().country = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_resource_url:
		RESULT.results.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_type:
		RESULT.results.back().type = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_uri:
		RESULT.results.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_catno:
		RESULT.results.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_year:
		RESULT.results.back().year = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_cover_image:
		RESULT.results.back().cover_image = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_master_url:
		RESULT.results.back().master_url = ::platform::string_t(value, length);
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_barcode:
		RESULT.results.back().barcode.emplace_back(value, length);
		break;
	case StateKey::search_results_results_format:
		RESULT.results.back().format.emplace_back(value, length);
		break;
	case StateKey::search_results_results_label:
		RESULT.results.back().label.emplace_back(value, length);
		break;
	case StateKey::search_results_results_style:
		RESULT.results.back().style.emplace_back(value, length);
		break;
	case StateKey::search_results_results_genre:
		RESULT.results.back().genre.emplace_back(value, length);
		break;
	default:
		return false;
	}
	return true;
}
bool search_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::search_results_results_user_data_in_collection:
		RESULT.results.back().user_data.in_collection = value;
		m_state = StateKey::search_results_results_user_data;
		break;
	case StateKey::search_results_results_user_data_in_wantlist:
		RESULT.results.back().user_data.in_wantlist = value;
		m_state = StateKey::search_results_results_user_data;
		break;
	default:
		return false;
	}
	return true;
}
bool search_parser::Double(double value)
{
	return false;
}
bool search_parser::Null()
{
	switch(m_state){
		case StateKey::search_results_pagination:
			m_state = StateKey::search_results;
			break;
		case StateKey::search_results_pagination_per_page:
			m_state = StateKey::search_results_pagination;
			break;
		case StateKey::search_results_pagination_items:
			m_state = StateKey::search_results_pagination;
			break;
		case StateKey::search_results_pagination_page:
			m_state = StateKey::search_results_pagination;
			break;
		case StateKey::search_results_pagination_pages:
			m_state = StateKey::search_results_pagination;
			break;
		case StateKey::search_results_pagination_urls:
			m_state = StateKey::search_results_pagination;
			break;
		case StateKey::search_results_pagination_urls_next:
			m_state = StateKey::search_results_pagination_urls;
			break;
		case StateKey::search_results_pagination_urls_last:
			m_state = StateKey::search_results_pagination_urls;
			break;
		case StateKey::search_results_pagination_urls_first:
			m_state = StateKey::search_results_pagination_urls;
			break;
		case StateKey::search_results_pagination_urls_prev:
			m_state = StateKey::search_results_pagination_urls;
			break;
		case StateKey::search_results_results:
			m_state = StateKey::search_results;
			break;
		case StateKey::search_results_results_id:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_master_id:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_thumb:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_title:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_country:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_resource_url:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_type:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_uri:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_catno:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_year:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_cover_image:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_master_url:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_barcode:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_format:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_label:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_style:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_genre:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_community:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_community_have:
			m_state = StateKey::search_results_results_community;
			break;
		case StateKey::search_results_results_community_want:
			m_state = StateKey::search_results_results_community;
			break;
		case StateKey::search_results_results_user_data:
			m_state = StateKey::search_results_results;
			break;
		case StateKey::search_results_results_user_data_in_collection:
			m_state = StateKey::search_results_results_user_data;
			break;
		case StateKey::search_results_results_user_data_in_wantlist:
			m_state = StateKey::search_results_results_user_data;
			break;
	}
	return true;
}
bool search_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::search_results_pagination_urls:
		if(length == 4 && platform::strcmp(str, STR("next")) == 0){
			m_state = StateKey::search_results_pagination_urls_next;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("last")) == 0){
			m_state = StateKey::search_results_pagination_urls_last;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("first")) == 0){
			m_state = StateKey::search_results_pagination_urls_first;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::search_results_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::search_results_pagination:
		if(length == 8 && platform::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::search_results_pagination_per_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("items")) == 0){
			m_state = StateKey::search_results_pagination_items;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("page")) == 0){
			m_state = StateKey::search_results_pagination_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::search_results_pagination_pages;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::search_results_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::search_results_results_community:
		if(length == 4 && platform::strcmp(str, STR("have")) == 0){
			m_state = StateKey::search_results_results_community_have;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("want")) == 0){
			m_state = StateKey::search_results_results_community_want;
		}
		else {
			return false;
		}
		break;
	case StateKey::search_results_results_user_data:
		if(length == 13 && platform::strcmp(str, STR("in_collection")) == 0){
			m_state = StateKey::search_results_results_user_data_in_collection;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("in_wantlist")) == 0){
			m_state = StateKey::search_results_results_user_data_in_wantlist;
		}
		else {
			return false;
		}
		break;
	case StateKey::search_results_results:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::search_results_results_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::search_results_results_master_id;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::search_results_results_thumb;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::search_results_results_title;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("country")) == 0){
			m_state = StateKey::search_results_results_country;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::search_results_results_resource_url;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::search_results_results_type;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::search_results_results_uri;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::search_results_results_catno;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::search_results_results_year;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("cover_image")) == 0){
			m_state = StateKey::search_results_results_cover_image;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::search_results_results_master_url;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("barcode")) == 0){
			m_state = StateKey::search_results_results_barcode;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("format")) == 0){
			m_state = StateKey::search_results_results_format;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("label")) == 0){
			m_state = StateKey::search_results_results_label;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("style")) == 0){
			m_state = StateKey::search_results_results_style;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("genre")) == 0){
			m_state = StateKey::search_results_results_genre;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("community")) == 0){
			m_state = StateKey::search_results_results_community;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("user_data")) == 0){
			m_state = StateKey::search_results_results_user_data;
		}
		else {
			return false;
		}
		break;
	case StateKey::search_results:
		if(length == 10 && platform::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::search_results_pagination;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("results")) == 0){
			m_state = StateKey::search_results_results;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool search_parser::StartArray()
{
	return true;
}
bool search_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::search_results_results:
		m_state = StateKey::search_results;
		break;
	case StateKey::search_results_results_barcode:
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_format:
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_label:
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_style:
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_genre:
		m_state = StateKey::search_results_results;
		break;
	}
	return true;
}

bool search_parser::StartObject()
{
	switch(m_state){
	case StateKey::search_results_results:
		RESULT.results.emplace_back();
		break;
	}
	return true;
}

bool search_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::search_results_pagination:
		m_state = StateKey::search_results;
		break;
	case StateKey::search_results_pagination_urls:
		m_state = StateKey::search_results_pagination;
		break;
	case StateKey::search_results_results_community:
		m_state = StateKey::search_results_results;
		break;
	case StateKey::search_results_results_user_data:
		m_state = StateKey::search_results_results;
		break;
	}
	return true;
}

search_parser::search_parser()
{
	m_state = StateKey::search_results;
}

} // namespace discogs
} // namespace result
