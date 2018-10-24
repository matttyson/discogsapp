/* clang-format off */
#include "wantlist_parser.hpp"
#include "porting.h"
namespace discogs {
namespace parser {

enum class StateKey {
	wantlist,
	wantlist_pagination,
	wantlist_pagination_per_page,
	wantlist_pagination_items,
	wantlist_pagination_page,
	wantlist_pagination_pages,
	wantlist_pagination_urls,
	wantlist_pagination_urls_next,
	wantlist_pagination_urls_last,
	wantlist_pagination_urls_first,
	wantlist_pagination_urls_prev,
	wantlist_wants,
	wantlist_wants_rating,
	wantlist_wants_id,
	wantlist_wants_resource_url,
	wantlist_wants_date_added,
	wantlist_wants_notes,
	wantlist_wants_basic_information,
	wantlist_wants_basic_information_id,
	wantlist_wants_basic_information_master_id,
	wantlist_wants_basic_information_year,
	wantlist_wants_basic_information_thumb,
	wantlist_wants_basic_information_title,
	wantlist_wants_basic_information_cover_image,
	wantlist_wants_basic_information_resource_url,
	wantlist_wants_basic_information_master_url,
	wantlist_wants_basic_information_labels,
	wantlist_wants_basic_information_labels_id,
	wantlist_wants_basic_information_labels_name,
	wantlist_wants_basic_information_labels_entity_type,
	wantlist_wants_basic_information_labels_catno,
	wantlist_wants_basic_information_labels_resource_url,
	wantlist_wants_basic_information_labels_entity_type_name,
	wantlist_wants_basic_information_formats,
	wantlist_wants_basic_information_formats_name,
	wantlist_wants_basic_information_formats_qty,
	wantlist_wants_basic_information_formats_text,
	wantlist_wants_basic_information_formats_descriptions,
	wantlist_wants_basic_information_artists,
	wantlist_wants_basic_information_artists_id,
	wantlist_wants_basic_information_artists_join,
	wantlist_wants_basic_information_artists_name,
	wantlist_wants_basic_information_artists_anv,
	wantlist_wants_basic_information_artists_tracks,
	wantlist_wants_basic_information_artists_role,
	wantlist_wants_basic_information_artists_resource_url,
	wantlist_wants_basic_information_notes,
	wantlist_wants_basic_information_notes_field_id,
	wantlist_wants_basic_information_notes_value,
};

bool wantlist_parser::Int(int value)
{
    return Number((int)value);
}

bool wantlist_parser::Uint(unsigned int value)
{
    return Number((int)value);
}

bool wantlist_parser::Int64(int64_t i)
{
    return false;
}

bool wantlist_parser::Uint64(uint64_t i)
{
    return false;
}

bool wantlist_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool wantlist_parser::Number(int value)
{
	switch(m_state){
	case StateKey::wantlist_pagination_per_page:
		wantlist_.pages.per_page = value;
		m_state = StateKey::wantlist_pagination;
		break;
	case StateKey::wantlist_pagination_items:
		wantlist_.pages.items = value;
		m_state = StateKey::wantlist_pagination;
		break;
	case StateKey::wantlist_pagination_page:
		wantlist_.pages.page = value;
		m_state = StateKey::wantlist_pagination;
		break;
	case StateKey::wantlist_pagination_pages:
		wantlist_.pages.pages = value;
		m_state = StateKey::wantlist_pagination;
		break;
	case StateKey::wantlist_wants_rating:
		wantlist_.want_.back().rating = value;
		m_state = StateKey::wantlist_wants;
		break;
	case StateKey::wantlist_wants_id:
		wantlist_.want_.back().id = value;
		m_state = StateKey::wantlist_wants;
		break;
	case StateKey::wantlist_wants_basic_information_id:
		wantlist_.want_.back().basic_information_.id = value;
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_master_id:
		wantlist_.want_.back().basic_information_.master_id = value;
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_year:
		wantlist_.want_.back().basic_information_.year = value;
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_labels_id:
		wantlist_.want_.back().basic_information_.labels.back().id = value;
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_artists_id:
		wantlist_.want_.back().basic_information_.artists.back().id = value;
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_notes_field_id:
		wantlist_.want_.back().basic_information_.notes.back().field_id = value;
		m_state = StateKey::wantlist_wants_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool wantlist_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::wantlist_pagination_urls_next:
		wantlist_.pages.links.next = string_t(value, length);
		m_state = StateKey::wantlist_pagination_urls;
		break;
	case StateKey::wantlist_pagination_urls_last:
		wantlist_.pages.links.last = string_t(value, length);
		m_state = StateKey::wantlist_pagination_urls;
		break;
	case StateKey::wantlist_pagination_urls_first:
		wantlist_.pages.links.first = string_t(value, length);
		m_state = StateKey::wantlist_pagination_urls;
		break;
	case StateKey::wantlist_pagination_urls_prev:
		wantlist_.pages.links.prev = string_t(value, length);
		m_state = StateKey::wantlist_pagination_urls;
		break;
	case StateKey::wantlist_wants_resource_url:
		wantlist_.want_.back().resource_url = string_t(value, length);
		m_state = StateKey::wantlist_wants;
		break;
	case StateKey::wantlist_wants_date_added:
		wantlist_.want_.back().date_added = string_t(value, length);
		m_state = StateKey::wantlist_wants;
		break;
	case StateKey::wantlist_wants_notes:
		wantlist_.want_.back().notes = string_t(value, length);
		m_state = StateKey::wantlist_wants;
		break;
	case StateKey::wantlist_wants_basic_information_thumb:
		wantlist_.want_.back().basic_information_.thumb = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_title:
		wantlist_.want_.back().basic_information_.title = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_cover_image:
		wantlist_.want_.back().basic_information_.cover_image = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_resource_url:
		wantlist_.want_.back().basic_information_.resource_url = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_master_url:
		wantlist_.want_.back().basic_information_.master_url = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_labels_name:
		wantlist_.want_.back().basic_information_.labels.back().name = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_labels_entity_type:
		wantlist_.want_.back().basic_information_.labels.back().entity_type = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_labels_catno:
		wantlist_.want_.back().basic_information_.labels.back().catno = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_labels_resource_url:
		wantlist_.want_.back().basic_information_.labels.back().resource_url = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_labels_entity_type_name:
		wantlist_.want_.back().basic_information_.labels.back().entity_type_name = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_labels;
		break;
	case StateKey::wantlist_wants_basic_information_formats_name:
		wantlist_.want_.back().basic_information_.formats.back().name = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_formats;
		break;
	case StateKey::wantlist_wants_basic_information_formats_qty:
		wantlist_.want_.back().basic_information_.formats.back().qty = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_formats;
		break;
	case StateKey::wantlist_wants_basic_information_formats_text:
		wantlist_.want_.back().basic_information_.formats.back().text = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_formats;
		break;
	case StateKey::wantlist_wants_basic_information_formats_descriptions:
		wantlist_.want_.back().basic_information_.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::wantlist_wants_basic_information_artists_join:
		wantlist_.want_.back().basic_information_.artists.back().join = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_artists_name:
		wantlist_.want_.back().basic_information_.artists.back().name = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_artists_anv:
		wantlist_.want_.back().basic_information_.artists.back().anv = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_artists_tracks:
		wantlist_.want_.back().basic_information_.artists.back().tracks = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_artists_role:
		wantlist_.want_.back().basic_information_.artists.back().role = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_artists_resource_url:
		wantlist_.want_.back().basic_information_.artists.back().resource_url = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_artists;
		break;
	case StateKey::wantlist_wants_basic_information_notes_value:
		wantlist_.want_.back().basic_information_.notes.back().value = string_t(value, length);
		m_state = StateKey::wantlist_wants_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool wantlist_parser::Bool(bool value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool wantlist_parser::Double(double value)
{
	switch(m_state){
	default:
		return false;
	}
	return true;
}
bool wantlist_parser::Null()
{
	switch(m_state){
		case StateKey::wantlist_pagination:
			m_state = StateKey::wantlist;
			break;
		case StateKey::wantlist_pagination_per_page:
			m_state = StateKey::wantlist_pagination;
			break;
		case StateKey::wantlist_pagination_items:
			m_state = StateKey::wantlist_pagination;
			break;
		case StateKey::wantlist_pagination_page:
			m_state = StateKey::wantlist_pagination;
			break;
		case StateKey::wantlist_pagination_pages:
			m_state = StateKey::wantlist_pagination;
			break;
		case StateKey::wantlist_pagination_urls:
			m_state = StateKey::wantlist_pagination;
			break;
		case StateKey::wantlist_pagination_urls_next:
			m_state = StateKey::wantlist_pagination_urls;
			break;
		case StateKey::wantlist_pagination_urls_last:
			m_state = StateKey::wantlist_pagination_urls;
			break;
		case StateKey::wantlist_pagination_urls_first:
			m_state = StateKey::wantlist_pagination_urls;
			break;
		case StateKey::wantlist_pagination_urls_prev:
			m_state = StateKey::wantlist_pagination_urls;
			break;
		case StateKey::wantlist_wants:
			m_state = StateKey::wantlist;
			break;
		case StateKey::wantlist_wants_rating:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_id:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_resource_url:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_date_added:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_notes:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_basic_information:
			m_state = StateKey::wantlist_wants;
			break;
		case StateKey::wantlist_wants_basic_information_id:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_master_id:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_year:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_thumb:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_title:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_cover_image:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_resource_url:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_master_url:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_labels:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_labels_id:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_labels_name:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_labels_entity_type:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_labels_catno:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_labels_resource_url:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_labels_entity_type_name:
			m_state = StateKey::wantlist_wants_basic_information_labels;
			break;
		case StateKey::wantlist_wants_basic_information_formats:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_formats_name:
			m_state = StateKey::wantlist_wants_basic_information_formats;
			break;
		case StateKey::wantlist_wants_basic_information_formats_qty:
			m_state = StateKey::wantlist_wants_basic_information_formats;
			break;
		case StateKey::wantlist_wants_basic_information_formats_text:
			m_state = StateKey::wantlist_wants_basic_information_formats;
			break;
		case StateKey::wantlist_wants_basic_information_formats_descriptions:
			m_state = StateKey::wantlist_wants_basic_information_formats;
			break;
		case StateKey::wantlist_wants_basic_information_artists:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_artists_id:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_join:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_name:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_anv:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_tracks:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_role:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_artists_resource_url:
			m_state = StateKey::wantlist_wants_basic_information_artists;
			break;
		case StateKey::wantlist_wants_basic_information_notes:
			m_state = StateKey::wantlist_wants_basic_information;
			break;
		case StateKey::wantlist_wants_basic_information_notes_field_id:
			m_state = StateKey::wantlist_wants_basic_information_notes;
			break;
		case StateKey::wantlist_wants_basic_information_notes_value:
			m_state = StateKey::wantlist_wants_basic_information_notes;
			break;
	}
	return true;
}
bool wantlist_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::wantlist_pagination_urls:
		if(length == 4 && discogs::strcmp(str, STR("next")) == 0){
			m_state = StateKey::wantlist_pagination_urls_next;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("last")) == 0){
			m_state = StateKey::wantlist_pagination_urls_last;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("first")) == 0){
			m_state = StateKey::wantlist_pagination_urls_first;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::wantlist_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_pagination:
		if(length == 8 && discogs::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::wantlist_pagination_per_page;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("items")) == 0){
			m_state = StateKey::wantlist_pagination_items;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("page")) == 0){
			m_state = StateKey::wantlist_pagination_page;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::wantlist_pagination_pages;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::wantlist_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants_basic_information_labels:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_name;
		}
		else
		if(length == 11 && discogs::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_entity_type;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_catno;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_resource_url;
		}
		else
		if(length == 16 && discogs::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants_basic_information_formats:
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_formats_name;
		}
		else
		if(length == 3 && discogs::strcmp(str, STR("qty")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_formats_qty;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("text")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_formats_text;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("descriptions")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants_basic_information_artists:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("join")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_join;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("name")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_name;
		}
		else
		if(length == 3 && discogs::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_anv;
		}
		else
		if(length == 6 && discogs::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_tracks;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("role")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_role;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants_basic_information_notes:
		if(length == 8 && discogs::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_notes_field_id;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("value")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants_basic_information:
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_id;
		}
		else
		if(length == 9 && discogs::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_master_id;
		}
		else
		if(length == 4 && discogs::strcmp(str, STR("year")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_year;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_thumb;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("title")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_title;
		}
		else
		if(length == 11 && discogs::strcmp(str, STR("cover_image")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_cover_image;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_resource_url;
		}
		else
		if(length == 10 && discogs::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_master_url;
		}
		else
		if(length == 6 && discogs::strcmp(str, STR("labels")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_labels;
		}
		else
		if(length == 7 && discogs::strcmp(str, STR("formats")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_formats;
		}
		else
		if(length == 7 && discogs::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_artists;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::wantlist_wants_basic_information_notes;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist_wants:
		if(length == 6 && discogs::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::wantlist_wants_rating;
		}
		else
		if(length == 2 && discogs::strcmp(str, STR("id")) == 0){
			m_state = StateKey::wantlist_wants_id;
		}
		else
		if(length == 12 && discogs::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::wantlist_wants_resource_url;
		}
		else
		if(length == 10 && discogs::strcmp(str, STR("date_added")) == 0){
			m_state = StateKey::wantlist_wants_date_added;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::wantlist_wants_notes;
		}
		else
		if(length == 17 && discogs::strcmp(str, STR("basic_information")) == 0){
			m_state = StateKey::wantlist_wants_basic_information;
		}
		else {
			return false;
		}
		break;
	case StateKey::wantlist:
		if(length == 10 && discogs::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::wantlist_pagination;
		}
		else
		if(length == 5 && discogs::strcmp(str, STR("wants")) == 0){
			m_state = StateKey::wantlist_wants;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool wantlist_parser::StartArray()
{
	return true;
}
bool wantlist_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::wantlist_wants:
		m_state = StateKey::wantlist;
		break;
	case StateKey::wantlist_wants_basic_information_labels:
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_formats:
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_formats_descriptions:
		m_state = StateKey::wantlist_wants_basic_information_formats;
		break;
	case StateKey::wantlist_wants_basic_information_artists:
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	case StateKey::wantlist_wants_basic_information_notes:
		m_state = StateKey::wantlist_wants_basic_information;
		break;
	}
	return true;
}

bool wantlist_parser::StartObject()
{
	switch(m_state){
	case StateKey::wantlist_wants:
		wantlist_.want_.emplace_back();
		break;
	case StateKey::wantlist_wants_basic_information_labels:
		wantlist_.want_.back().basic_information_.labels.emplace_back();
		break;
	case StateKey::wantlist_wants_basic_information_formats:
		wantlist_.want_.back().basic_information_.formats.emplace_back();
		break;
	case StateKey::wantlist_wants_basic_information_artists:
		wantlist_.want_.back().basic_information_.artists.emplace_back();
		break;
	case StateKey::wantlist_wants_basic_information_notes:
		wantlist_.want_.back().basic_information_.notes.emplace_back();
		break;
	}
	return true;
}

bool wantlist_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::wantlist_pagination:
		m_state = StateKey::wantlist;
		break;
	case StateKey::wantlist_pagination_urls:
		m_state = StateKey::wantlist_pagination;
		break;
	case StateKey::wantlist_wants_basic_information:
		m_state = StateKey::wantlist_wants;
		break;
	}
	return true;
}

wantlist_parser::wantlist_parser()
{
	m_state = StateKey::wantlist;
}

} // namespace discogs
} // namespace parser
