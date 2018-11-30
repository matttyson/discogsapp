/* clang-format off */
#include "folder_releases_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	folder_releases,
	folder_releases_pagination,
	folder_releases_pagination_per_page,
	folder_releases_pagination_items,
	folder_releases_pagination_page,
	folder_releases_pagination_pages,
	folder_releases_pagination_urls,
	folder_releases_pagination_urls_next,
	folder_releases_pagination_urls_last,
	folder_releases_pagination_urls_first,
	folder_releases_pagination_urls_prev,
	folder_releases_releases,
	folder_releases_releases_id,
	folder_releases_releases_instance_id,
	folder_releases_releases_rating,
	folder_releases_releases_folder_id,
	folder_releases_releases_date_added,
	folder_releases_releases_notes,
	folder_releases_releases_notes_field_id,
	folder_releases_releases_notes_value,
	folder_releases_releases_basic_information,
	folder_releases_releases_basic_information_id,
	folder_releases_releases_basic_information_master_id,
	folder_releases_releases_basic_information_year,
	folder_releases_releases_basic_information_thumb,
	folder_releases_releases_basic_information_title,
	folder_releases_releases_basic_information_cover_image,
	folder_releases_releases_basic_information_resource_url,
	folder_releases_releases_basic_information_master_url,
	folder_releases_releases_basic_information_labels,
	folder_releases_releases_basic_information_labels_id,
	folder_releases_releases_basic_information_labels_name,
	folder_releases_releases_basic_information_labels_entity_type,
	folder_releases_releases_basic_information_labels_catno,
	folder_releases_releases_basic_information_labels_resource_url,
	folder_releases_releases_basic_information_labels_entity_type_name,
	folder_releases_releases_basic_information_formats,
	folder_releases_releases_basic_information_formats_name,
	folder_releases_releases_basic_information_formats_qty,
	folder_releases_releases_basic_information_formats_text,
	folder_releases_releases_basic_information_formats_descriptions,
	folder_releases_releases_basic_information_artists,
	folder_releases_releases_basic_information_artists_id,
	folder_releases_releases_basic_information_artists_join,
	folder_releases_releases_basic_information_artists_name,
	folder_releases_releases_basic_information_artists_anv,
	folder_releases_releases_basic_information_artists_tracks,
	folder_releases_releases_basic_information_artists_role,
	folder_releases_releases_basic_information_artists_resource_url,
	folder_releases_releases_basic_information_notes,
	folder_releases_releases_basic_information_notes_field_id,
	folder_releases_releases_basic_information_notes_value,
};

bool folder_releases_parser::Int(int value)
{
	return Number((int)value);
}

bool folder_releases_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool folder_releases_parser::Int64(int64_t i)
{
	return false;
}

bool folder_releases_parser::Uint64(uint64_t i)
{
	return false;
}
bool folder_releases_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_releases_pagination_urls_next:
		RESULT.pages.links.next = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_last:
		RESULT.pages.links.last = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_first:
		RESULT.pages.links.first = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_prev:
		RESULT.pages.links.prev = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_releases_date_added:
		RESULT.release_.back().date_added = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_notes_value:
		RESULT.release_.back().notes.back().value = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_notes;
		break;
	case StateKey::folder_releases_releases_basic_information_thumb:
		RESULT.release_.back().basic_information_.thumb = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_title:
		RESULT.release_.back().basic_information_.title = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_cover_image:
		RESULT.release_.back().basic_information_.cover_image = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_resource_url:
		RESULT.release_.back().basic_information_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_master_url:
		RESULT.release_.back().basic_information_.master_url = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_name:
		RESULT.release_.back().basic_information_.labels.back().name = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_entity_type:
		RESULT.release_.back().basic_information_.labels.back().entity_type = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_catno:
		RESULT.release_.back().basic_information_.labels.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_resource_url:
		RESULT.release_.back().basic_information_.labels.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_entity_type_name:
		RESULT.release_.back().basic_information_.labels.back().entity_type_name = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_name:
		RESULT.release_.back().basic_information_.formats.back().name = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_qty:
		RESULT.release_.back().basic_information_.formats.back().qty = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_text:
		RESULT.release_.back().basic_information_.formats.back().text = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_descriptions:
		RESULT.release_.back().basic_information_.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::folder_releases_releases_basic_information_artists_join:
		RESULT.release_.back().basic_information_.artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_name:
		RESULT.release_.back().basic_information_.artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_anv:
		RESULT.release_.back().basic_information_.artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_tracks:
		RESULT.release_.back().basic_information_.artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_role:
		RESULT.release_.back().basic_information_.artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_resource_url:
		RESULT.release_.back().basic_information_.artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_notes_value:
		RESULT.release_.back().basic_information_.notes.back().value = ::platform::string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_releases_parser::Bool(bool value)
{
	return false;
}
bool folder_releases_parser::Double(double value)
{
	return false;
}
bool folder_releases_parser::Number(int value)
{
	switch(m_state){
	case StateKey::folder_releases_pagination_per_page:
		RESULT.pages.per_page = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_items:
		RESULT.pages.items = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_page:
		RESULT.pages.page = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_pages:
		RESULT.pages.pages = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_releases_id:
		RESULT.release_.back().id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_instance_id:
		RESULT.release_.back().instance_id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_rating:
		RESULT.release_.back().rating = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_folder_id:
		RESULT.release_.back().folder_id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_notes_field_id:
		RESULT.release_.back().notes.back().field_id = value;
		m_state = StateKey::folder_releases_releases_notes;
		break;
	case StateKey::folder_releases_releases_basic_information_id:
		RESULT.release_.back().basic_information_.id = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_master_id:
		RESULT.release_.back().basic_information_.master_id = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_year:
		RESULT.release_.back().basic_information_.year = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_id:
		RESULT.release_.back().basic_information_.labels.back().id = value;
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_id:
		RESULT.release_.back().basic_information_.artists.back().id = value;
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_notes_field_id:
		RESULT.release_.back().basic_information_.notes.back().field_id = value;
		m_state = StateKey::folder_releases_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_releases_parser::RawNumber(const Ch*, rapidjson::SizeType, bool)
{
	return false;
}

bool folder_releases_parser::Null()
{
	switch(m_state){
		case StateKey::folder_releases_pagination:
			m_state = StateKey::folder_releases;
			break;
		case StateKey::folder_releases_pagination_per_page:
			m_state = StateKey::folder_releases_pagination;
			break;
		case StateKey::folder_releases_pagination_items:
			m_state = StateKey::folder_releases_pagination;
			break;
		case StateKey::folder_releases_pagination_page:
			m_state = StateKey::folder_releases_pagination;
			break;
		case StateKey::folder_releases_pagination_pages:
			m_state = StateKey::folder_releases_pagination;
			break;
		case StateKey::folder_releases_pagination_urls:
			m_state = StateKey::folder_releases_pagination;
			break;
		case StateKey::folder_releases_pagination_urls_next:
			m_state = StateKey::folder_releases_pagination_urls;
			break;
		case StateKey::folder_releases_pagination_urls_last:
			m_state = StateKey::folder_releases_pagination_urls;
			break;
		case StateKey::folder_releases_pagination_urls_first:
			m_state = StateKey::folder_releases_pagination_urls;
			break;
		case StateKey::folder_releases_pagination_urls_prev:
			m_state = StateKey::folder_releases_pagination_urls;
			break;
		case StateKey::folder_releases_releases:
			m_state = StateKey::folder_releases;
			break;
		case StateKey::folder_releases_releases_id:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_instance_id:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_rating:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_folder_id:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_date_added:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_notes:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_notes_field_id:
			m_state = StateKey::folder_releases_releases_notes;
			break;
		case StateKey::folder_releases_releases_notes_value:
			m_state = StateKey::folder_releases_releases_notes;
			break;
		case StateKey::folder_releases_releases_basic_information:
			m_state = StateKey::folder_releases_releases;
			break;
		case StateKey::folder_releases_releases_basic_information_id:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_master_id:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_year:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_thumb:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_title:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_cover_image:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_resource_url:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_master_url:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_labels:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_id:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_name:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_entity_type:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_catno:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_resource_url:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_labels_entity_type_name:
			m_state = StateKey::folder_releases_releases_basic_information_labels;
			break;
		case StateKey::folder_releases_releases_basic_information_formats:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_formats_name:
			m_state = StateKey::folder_releases_releases_basic_information_formats;
			break;
		case StateKey::folder_releases_releases_basic_information_formats_qty:
			m_state = StateKey::folder_releases_releases_basic_information_formats;
			break;
		case StateKey::folder_releases_releases_basic_information_formats_text:
			m_state = StateKey::folder_releases_releases_basic_information_formats;
			break;
		case StateKey::folder_releases_releases_basic_information_formats_descriptions:
			m_state = StateKey::folder_releases_releases_basic_information_formats;
			break;
		case StateKey::folder_releases_releases_basic_information_artists:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_id:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_join:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_name:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_anv:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_tracks:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_role:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_artists_resource_url:
			m_state = StateKey::folder_releases_releases_basic_information_artists;
			break;
		case StateKey::folder_releases_releases_basic_information_notes:
			m_state = StateKey::folder_releases_releases_basic_information;
			break;
		case StateKey::folder_releases_releases_basic_information_notes_field_id:
			m_state = StateKey::folder_releases_releases_basic_information_notes;
			break;
		case StateKey::folder_releases_releases_basic_information_notes_value:
			m_state = StateKey::folder_releases_releases_basic_information_notes;
			break;
	}
	return true;
}
bool folder_releases_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_releases_pagination_urls:
		if(length == 4 && platform::strcmp(str, STR("next")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_next;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("last")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_last;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("first")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_first;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_pagination:
		if(length == 8 && platform::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::folder_releases_pagination_per_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("items")) == 0){
			m_state = StateKey::folder_releases_pagination_items;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("page")) == 0){
			m_state = StateKey::folder_releases_pagination_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::folder_releases_pagination_pages;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::folder_releases_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_notes:
		if(length == 8 && platform::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::folder_releases_releases_notes_field_id;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::folder_releases_releases_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_labels:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_name;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_entity_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_catno;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_resource_url;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_formats:
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("qty")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_qty;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("text")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_text;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("descriptions")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_notes:
		if(length == 8 && platform::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes_field_id;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_master_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_year;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_thumb;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_title;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("cover_image")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_cover_image;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_resource_url;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_master_url;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("labels")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("formats")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_id;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("instance_id")) == 0){
			m_state = StateKey::folder_releases_releases_instance_id;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::folder_releases_releases_rating;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("folder_id")) == 0){
			m_state = StateKey::folder_releases_releases_folder_id;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("date_added")) == 0){
			m_state = StateKey::folder_releases_releases_date_added;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::folder_releases_releases_notes;
		}
		else
		if(length == 17 && platform::strcmp(str, STR("basic_information")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases:
		if(length == 10 && platform::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::folder_releases_pagination;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("releases")) == 0){
			m_state = StateKey::folder_releases_releases;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool folder_releases_parser::StartArray()
{
	return true;
}
bool folder_releases_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::folder_releases_releases:
		m_state = StateKey::folder_releases;
		break;
	case StateKey::folder_releases_releases_notes:
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_basic_information_labels:
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_formats:
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_descriptions:
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_artists:
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_notes:
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	}
	return true;
}

bool folder_releases_parser::StartObject()
{
	switch(m_state){
	case StateKey::folder_releases_releases:
		RESULT.release_.emplace_back();
		break;
	case StateKey::folder_releases_releases_notes:
		RESULT.release_.back().notes.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_labels:
		RESULT.release_.back().basic_information_.labels.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_formats:
		RESULT.release_.back().basic_information_.formats.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_artists:
		RESULT.release_.back().basic_information_.artists.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_notes:
		RESULT.release_.back().basic_information_.notes.emplace_back();
		break;
	}
	return true;
}

bool folder_releases_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::folder_releases_pagination:
		m_state = StateKey::folder_releases;
		break;
	case StateKey::folder_releases_pagination_urls:
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_releases_basic_information:
		m_state = StateKey::folder_releases_releases;
		break;
	}
	return true;
}

folder_releases_parser::folder_releases_parser()
{
	m_state = StateKey::folder_releases;
}

} // namespace discogs
} // namespace parser
