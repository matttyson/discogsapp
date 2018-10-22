/* clang-format off */
#include "folder_releases_parser.hpp"
#include "porting.h"
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

bool folder_releases_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool folder_releases_parser::Number(int value)
{
	switch(m_state){
	case StateKey::folder_releases_pagination_per_page:
		folder_release.pages.per_page = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_items:
		folder_release.pages.items = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_page:
		folder_release.pages.page = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_pagination_pages:
		folder_release.pages.pages = value;
		m_state = StateKey::folder_releases_pagination;
		break;
	case StateKey::folder_releases_releases_id:
		folder_release.release_.back().id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_instance_id:
		folder_release.release_.back().instance_id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_rating:
		folder_release.release_.back().rating = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_folder_id:
		folder_release.release_.back().folder_id = value;
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_notes_field_id:
		folder_release.release_.back().notes.back().field_id = value;
		m_state = StateKey::folder_releases_releases_notes;
		break;
	case StateKey::folder_releases_releases_basic_information_id:
		folder_release.release_.back().basic_information_.id = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_master_id:
		folder_release.release_.back().basic_information_.master_id = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_year:
		folder_release.release_.back().basic_information_.year = value;
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_id:
		folder_release.release_.back().basic_information_.labels.back().id = value;
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_id:
		folder_release.release_.back().basic_information_.artists.back().id = value;
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_notes_field_id:
		folder_release.release_.back().basic_information_.notes.back().field_id = value;
		m_state = StateKey::folder_releases_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_releases_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::folder_releases_pagination_urls_next:
		folder_release.pages.links.next = string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_last:
		folder_release.pages.links.last = string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_first:
		folder_release.pages.links.first = string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_pagination_urls_prev:
		folder_release.pages.links.prev = string_t(value, length);
		m_state = StateKey::folder_releases_pagination_urls;
		break;
	case StateKey::folder_releases_releases_date_added:
		folder_release.release_.back().date_added = string_t(value, length);
		m_state = StateKey::folder_releases_releases;
		break;
	case StateKey::folder_releases_releases_notes_value:
		folder_release.release_.back().notes.back().value = string_t(value, length);
		m_state = StateKey::folder_releases_releases_notes;
		break;
	case StateKey::folder_releases_releases_basic_information_thumb:
		folder_release.release_.back().basic_information_.thumb = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_title:
		folder_release.release_.back().basic_information_.title = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_cover_image:
		folder_release.release_.back().basic_information_.cover_image = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_resource_url:
		folder_release.release_.back().basic_information_.resource_url = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_master_url:
		folder_release.release_.back().basic_information_.master_url = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_name:
		folder_release.release_.back().basic_information_.labels.back().name = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_entity_type:
		folder_release.release_.back().basic_information_.labels.back().entity_type = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_catno:
		folder_release.release_.back().basic_information_.labels.back().catno = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_resource_url:
		folder_release.release_.back().basic_information_.labels.back().resource_url = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_labels_entity_type_name:
		folder_release.release_.back().basic_information_.labels.back().entity_type_name = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_labels;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_name:
		folder_release.release_.back().basic_information_.formats.back().name = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_qty:
		folder_release.release_.back().basic_information_.formats.back().qty = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_text:
		folder_release.release_.back().basic_information_.formats.back().text = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_formats;
		break;
	case StateKey::folder_releases_releases_basic_information_formats_descriptions:
		folder_release.release_.back().basic_information_.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::folder_releases_releases_basic_information_artists_join:
		folder_release.release_.back().basic_information_.artists.back().join = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_name:
		folder_release.release_.back().basic_information_.artists.back().name = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_anv:
		folder_release.release_.back().basic_information_.artists.back().anv = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_tracks:
		folder_release.release_.back().basic_information_.artists.back().tracks = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_role:
		folder_release.release_.back().basic_information_.artists.back().role = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_artists_resource_url:
		folder_release.release_.back().basic_information_.artists.back().resource_url = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_artists;
		break;
	case StateKey::folder_releases_releases_basic_information_notes_value:
		folder_release.release_.back().basic_information_.notes.back().value = string_t(value, length);
		m_state = StateKey::folder_releases_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_releases_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool folder_releases_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
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
		if(length == 4 && discogs::strcmp(str, STR("next")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_next;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("last")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_last;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("first")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_first;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::folder_releases_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_pagination:
		if(length == 8 && discogs::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::folder_releases_pagination_per_page;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("items")) == 0){
			m_state = StateKey::folder_releases_pagination_items;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("page")) == 0){
			m_state = StateKey::folder_releases_pagination_page;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::folder_releases_pagination_pages;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::folder_releases_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_notes:
		if(length == 8 && discogs::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::folder_releases_releases_notes_field_id;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("value")) == 0){
			m_state = StateKey::folder_releases_releases_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_labels:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_name;
		}
		else
		if(length == 11 && discogs::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_entity_type;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_catno;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_resource_url;
		}
		else
		if(length == 16 && discogs::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_formats:
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_name;
		}
		else
		if(length == 3 && discogs::strcmp(str, STR("qty")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_qty;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("text")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_text;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("descriptions")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_artists:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("join")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_join;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_name;
		}
		else
		if(length == 3 && discogs::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_anv;
		}
		else
		if(length == 6 && discogs::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_tracks;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("role")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_role;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information_notes:
		if(length == 8 && discogs::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes_field_id;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("value")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases_basic_information:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_id;
		}
		else
		if(length == 9 && discogs::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_master_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("year")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_year;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_thumb;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("title")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_title;
		}
		else
		if(length == 11 && discogs::strcmp(str, STR("cover_image")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_cover_image;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_resource_url;
		}
		else
		if(length == 10 && discogs::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_master_url;
		}
		else
		if(length == 6 && discogs::strcmp(str, STR("labels")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_labels;
		}
		else
		if(length == 7 && discogs::strcmp(str, STR("formats")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_formats;
		}
		else
		if(length == 7 && discogs::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_artists;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information_notes;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases_releases:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::folder_releases_releases_id;
		}
		else
		if(length == 11 && discogs::strcmp(str, STR("instance_id")) == 0){
			m_state = StateKey::folder_releases_releases_instance_id;
		}
		else
		if(length == 6 && discogs::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::folder_releases_releases_rating;
		}
		else
		if(length == 9 && discogs::strcmp(str, STR("folder_id")) == 0){
			m_state = StateKey::folder_releases_releases_folder_id;
		}
		else
		if(length == 10 && discogs::strcmp(str, STR("date_added")) == 0){
			m_state = StateKey::folder_releases_releases_date_added;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::folder_releases_releases_notes;
		}
		else
		if(length == 17 && discogs::strcmp(str, STR("basic_information")) == 0){
			m_state = StateKey::folder_releases_releases_basic_information;
		}
		else {
			return false;
		}
		break;
	case StateKey::folder_releases:
		if(length == 10 && discogs::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::folder_releases_pagination;
		}
		else
		if(length == 8 && discogs::strcmp(str, STR("releases")) == 0){
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
		folder_release.release_.emplace_back();
		break;
	case StateKey::folder_releases_releases_notes:
		folder_release.release_.back().notes.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_labels:
		folder_release.release_.back().basic_information_.labels.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_formats:
		folder_release.release_.back().basic_information_.formats.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_artists:
		folder_release.release_.back().basic_information_.artists.emplace_back();
		break;
	case StateKey::folder_releases_releases_basic_information_notes:
		folder_release.release_.back().basic_information_.notes.emplace_back();
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
