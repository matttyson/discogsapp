/* clang-format off */
#include "folder_collection_releases_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	collection_release,
	collection_release_pagination,
	collection_release_pagination_per_page,
	collection_release_pagination_items,
	collection_release_pagination_page,
	collection_release_pagination_pages,
	collection_release_pagination_urls,
	collection_release_pagination_urls_next,
	collection_release_pagination_urls_last,
	collection_release_pagination_urls_first,
	collection_release_pagination_urls_prev,
	collection_release_releases,
	collection_release_releases_id,
	collection_release_releases_instance_id,
	collection_release_releases_rating,
	collection_release_releases_folder_id,
	collection_release_releases_date_added,
	collection_release_releases_basic_information,
	collection_release_releases_basic_information_id,
	collection_release_releases_basic_information_master_id,
	collection_release_releases_basic_information_year,
	collection_release_releases_basic_information_thumb,
	collection_release_releases_basic_information_title,
	collection_release_releases_basic_information_cover_image,
	collection_release_releases_basic_information_resource_url,
	collection_release_releases_basic_information_master_url,
	collection_release_releases_basic_information_labels,
	collection_release_releases_basic_information_labels_id,
	collection_release_releases_basic_information_labels_name,
	collection_release_releases_basic_information_labels_entity_type,
	collection_release_releases_basic_information_labels_catno,
	collection_release_releases_basic_information_labels_resource_url,
	collection_release_releases_basic_information_labels_entity_type_name,
	collection_release_releases_basic_information_formats,
	collection_release_releases_basic_information_formats_name,
	collection_release_releases_basic_information_formats_qty,
	collection_release_releases_basic_information_formats_text,
	collection_release_releases_basic_information_formats_descriptions,
	collection_release_releases_basic_information_artists,
	collection_release_releases_basic_information_artists_id,
	collection_release_releases_basic_information_artists_join,
	collection_release_releases_basic_information_artists_name,
	collection_release_releases_basic_information_artists_anv,
	collection_release_releases_basic_information_artists_tracks,
	collection_release_releases_basic_information_artists_role,
	collection_release_releases_basic_information_artists_resource_url,
	collection_release_releases_basic_information_notes,
	collection_release_releases_basic_information_notes_field_id,
	collection_release_releases_basic_information_notes_value,
};

bool folder_collection_releases_parser::Int(int value)
{
	return Number((int)value);
}

bool folder_collection_releases_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool folder_collection_releases_parser::Int64(int64_t i)
{
	return false;
}

bool folder_collection_releases_parser::Uint64(uint64_t i)
{
	return false;
}

bool folder_collection_releases_parser::RawNumber(const Ch * str, rapidjson::SizeType length, bool copy)
{
	return false;
}
bool folder_collection_releases_parser::Number(int value)
{
	switch(m_state){
	case StateKey::collection_release_pagination_per_page:
		RESULT.pages.per_page = value;
		m_state = StateKey::collection_release_pagination;
		break;
	case StateKey::collection_release_pagination_items:
		RESULT.pages.items = value;
		m_state = StateKey::collection_release_pagination;
		break;
	case StateKey::collection_release_pagination_page:
		RESULT.pages.page = value;
		m_state = StateKey::collection_release_pagination;
		break;
	case StateKey::collection_release_pagination_pages:
		RESULT.pages.pages = value;
		m_state = StateKey::collection_release_pagination;
		break;
	case StateKey::collection_release_releases_id:
		RESULT.releases.back().id = value;
		m_state = StateKey::collection_release_releases;
		break;
	case StateKey::collection_release_releases_instance_id:
		RESULT.releases.back().instance_id = value;
		m_state = StateKey::collection_release_releases;
		break;
	case StateKey::collection_release_releases_rating:
		RESULT.releases.back().rating = value;
		m_state = StateKey::collection_release_releases;
		break;
	case StateKey::collection_release_releases_folder_id:
		RESULT.releases.back().folder_id = value;
		m_state = StateKey::collection_release_releases;
		break;
	case StateKey::collection_release_releases_basic_information_id:
		RESULT.releases.back().basic_information_.id = value;
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_master_id:
		RESULT.releases.back().basic_information_.master_id = value;
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_year:
		RESULT.releases.back().basic_information_.year = value;
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_labels_id:
		RESULT.releases.back().basic_information_.labels.back().id = value;
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_artists_id:
		RESULT.releases.back().basic_information_.artists.back().id = value;
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_notes_field_id:
		RESULT.releases.back().basic_information_.notes.back().field_id = value;
		m_state = StateKey::collection_release_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_collection_releases_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::collection_release_pagination_urls_next:
		RESULT.pages.links.next = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_pagination_urls;
		break;
	case StateKey::collection_release_pagination_urls_last:
		RESULT.pages.links.last = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_pagination_urls;
		break;
	case StateKey::collection_release_pagination_urls_first:
		RESULT.pages.links.first = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_pagination_urls;
		break;
	case StateKey::collection_release_pagination_urls_prev:
		RESULT.pages.links.prev = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_pagination_urls;
		break;
	case StateKey::collection_release_releases_date_added:
		RESULT.releases.back().date_added = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases;
		break;
	case StateKey::collection_release_releases_basic_information_thumb:
		RESULT.releases.back().basic_information_.thumb = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_title:
		RESULT.releases.back().basic_information_.title = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_cover_image:
		RESULT.releases.back().basic_information_.cover_image = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_resource_url:
		RESULT.releases.back().basic_information_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_master_url:
		RESULT.releases.back().basic_information_.master_url = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_labels_name:
		RESULT.releases.back().basic_information_.labels.back().name = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_labels_entity_type:
		RESULT.releases.back().basic_information_.labels.back().entity_type = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_labels_catno:
		RESULT.releases.back().basic_information_.labels.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_labels_resource_url:
		RESULT.releases.back().basic_information_.labels.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_labels_entity_type_name:
		RESULT.releases.back().basic_information_.labels.back().entity_type_name = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_labels;
		break;
	case StateKey::collection_release_releases_basic_information_formats_name:
		RESULT.releases.back().basic_information_.formats.back().name = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_formats;
		break;
	case StateKey::collection_release_releases_basic_information_formats_qty:
		RESULT.releases.back().basic_information_.formats.back().qty = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_formats;
		break;
	case StateKey::collection_release_releases_basic_information_formats_text:
		RESULT.releases.back().basic_information_.formats.back().text = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_formats;
		break;
	case StateKey::collection_release_releases_basic_information_formats_descriptions:
		RESULT.releases.back().basic_information_.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::collection_release_releases_basic_information_artists_join:
		RESULT.releases.back().basic_information_.artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_artists_name:
		RESULT.releases.back().basic_information_.artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_artists_anv:
		RESULT.releases.back().basic_information_.artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_artists_tracks:
		RESULT.releases.back().basic_information_.artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_artists_role:
		RESULT.releases.back().basic_information_.artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_artists_resource_url:
		RESULT.releases.back().basic_information_.artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_artists;
		break;
	case StateKey::collection_release_releases_basic_information_notes_value:
		RESULT.releases.back().basic_information_.notes.back().value = ::platform::string_t(value, length);
		m_state = StateKey::collection_release_releases_basic_information_notes;
		break;
	default:
		return false;
	}
	return true;
}
bool folder_collection_releases_parser::Bool(bool value)
{
	return false;
}
bool folder_collection_releases_parser::Double(double value)
{
	return false;
}
bool folder_collection_releases_parser::Null()
{
	switch(m_state){
		case StateKey::collection_release_pagination:
			m_state = StateKey::collection_release;
			break;
		case StateKey::collection_release_pagination_per_page:
			m_state = StateKey::collection_release_pagination;
			break;
		case StateKey::collection_release_pagination_items:
			m_state = StateKey::collection_release_pagination;
			break;
		case StateKey::collection_release_pagination_page:
			m_state = StateKey::collection_release_pagination;
			break;
		case StateKey::collection_release_pagination_pages:
			m_state = StateKey::collection_release_pagination;
			break;
		case StateKey::collection_release_pagination_urls:
			m_state = StateKey::collection_release_pagination;
			break;
		case StateKey::collection_release_pagination_urls_next:
			m_state = StateKey::collection_release_pagination_urls;
			break;
		case StateKey::collection_release_pagination_urls_last:
			m_state = StateKey::collection_release_pagination_urls;
			break;
		case StateKey::collection_release_pagination_urls_first:
			m_state = StateKey::collection_release_pagination_urls;
			break;
		case StateKey::collection_release_pagination_urls_prev:
			m_state = StateKey::collection_release_pagination_urls;
			break;
		case StateKey::collection_release_releases:
			m_state = StateKey::collection_release;
			break;
		case StateKey::collection_release_releases_id:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_instance_id:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_rating:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_folder_id:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_date_added:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_basic_information:
			m_state = StateKey::collection_release_releases;
			break;
		case StateKey::collection_release_releases_basic_information_id:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_master_id:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_year:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_thumb:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_title:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_cover_image:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_resource_url:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_master_url:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_labels:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_labels_id:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_labels_name:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_labels_entity_type:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_labels_catno:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_labels_resource_url:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_labels_entity_type_name:
			m_state = StateKey::collection_release_releases_basic_information_labels;
			break;
		case StateKey::collection_release_releases_basic_information_formats:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_formats_name:
			m_state = StateKey::collection_release_releases_basic_information_formats;
			break;
		case StateKey::collection_release_releases_basic_information_formats_qty:
			m_state = StateKey::collection_release_releases_basic_information_formats;
			break;
		case StateKey::collection_release_releases_basic_information_formats_text:
			m_state = StateKey::collection_release_releases_basic_information_formats;
			break;
		case StateKey::collection_release_releases_basic_information_formats_descriptions:
			m_state = StateKey::collection_release_releases_basic_information_formats;
			break;
		case StateKey::collection_release_releases_basic_information_artists:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_artists_id:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_join:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_name:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_anv:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_tracks:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_role:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_artists_resource_url:
			m_state = StateKey::collection_release_releases_basic_information_artists;
			break;
		case StateKey::collection_release_releases_basic_information_notes:
			m_state = StateKey::collection_release_releases_basic_information;
			break;
		case StateKey::collection_release_releases_basic_information_notes_field_id:
			m_state = StateKey::collection_release_releases_basic_information_notes;
			break;
		case StateKey::collection_release_releases_basic_information_notes_value:
			m_state = StateKey::collection_release_releases_basic_information_notes;
			break;
	}
	return true;
}
bool folder_collection_releases_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::collection_release_pagination_urls:
		if(length == 4 && platform::strcmp(str, STR("next")) == 0){
			m_state = StateKey::collection_release_pagination_urls_next;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("last")) == 0){
			m_state = StateKey::collection_release_pagination_urls_last;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("first")) == 0){
			m_state = StateKey::collection_release_pagination_urls_first;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::collection_release_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_pagination:
		if(length == 8 && platform::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::collection_release_pagination_per_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("items")) == 0){
			m_state = StateKey::collection_release_pagination_items;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("page")) == 0){
			m_state = StateKey::collection_release_pagination_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::collection_release_pagination_pages;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::collection_release_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases_basic_information_labels:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_name;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_entity_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_catno;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_resource_url;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases_basic_information_formats:
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_formats_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("qty")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_formats_qty;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("text")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_formats_text;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("descriptions")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases_basic_information_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases_basic_information_notes:
		if(length == 8 && platform::strcmp(str, STR("field_id")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_notes_field_id;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_notes_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases_basic_information:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_master_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_year;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_thumb;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_title;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("cover_image")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_cover_image;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_resource_url;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_master_url;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("labels")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_labels;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("formats")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_formats;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_artists;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::collection_release_releases_basic_information_notes;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release_releases:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::collection_release_releases_id;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("instance_id")) == 0){
			m_state = StateKey::collection_release_releases_instance_id;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::collection_release_releases_rating;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("folder_id")) == 0){
			m_state = StateKey::collection_release_releases_folder_id;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("date_added")) == 0){
			m_state = StateKey::collection_release_releases_date_added;
		}
		else
		if(length == 17 && platform::strcmp(str, STR("basic_information")) == 0){
			m_state = StateKey::collection_release_releases_basic_information;
		}
		else {
			return false;
		}
		break;
	case StateKey::collection_release:
		if(length == 10 && platform::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::collection_release_pagination;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("releases")) == 0){
			m_state = StateKey::collection_release_releases;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool folder_collection_releases_parser::StartArray()
{
	return true;
}
bool folder_collection_releases_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::collection_release_releases:
		m_state = StateKey::collection_release;
		break;
	case StateKey::collection_release_releases_basic_information_labels:
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_formats:
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_formats_descriptions:
		m_state = StateKey::collection_release_releases_basic_information_formats;
		break;
	case StateKey::collection_release_releases_basic_information_artists:
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	case StateKey::collection_release_releases_basic_information_notes:
		m_state = StateKey::collection_release_releases_basic_information;
		break;
	}
	return true;
}

bool folder_collection_releases_parser::StartObject()
{
	switch(m_state){
	case StateKey::collection_release_releases:
		RESULT.releases.emplace_back();
		break;
	case StateKey::collection_release_releases_basic_information_labels:
		RESULT.releases.back().basic_information_.labels.emplace_back();
		break;
	case StateKey::collection_release_releases_basic_information_formats:
		RESULT.releases.back().basic_information_.formats.emplace_back();
		break;
	case StateKey::collection_release_releases_basic_information_artists:
		RESULT.releases.back().basic_information_.artists.emplace_back();
		break;
	case StateKey::collection_release_releases_basic_information_notes:
		RESULT.releases.back().basic_information_.notes.emplace_back();
		break;
	}
	return true;
}

bool folder_collection_releases_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::collection_release_pagination:
		m_state = StateKey::collection_release;
		break;
	case StateKey::collection_release_pagination_urls:
		m_state = StateKey::collection_release_pagination;
		break;
	case StateKey::collection_release_releases_basic_information:
		m_state = StateKey::collection_release_releases;
		break;
	}
	return true;
}

folder_collection_releases_parser::folder_collection_releases_parser()
{
	m_state = StateKey::collection_release;
}

} // namespace discogs
} // namespace parser
