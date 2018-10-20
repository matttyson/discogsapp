/* clang-format off */
#include "release_parser.hpp"

namespace discogs {
namespace parser {
namespace release {

enum class StateKey {
	release,
	release_year,
	release_id,
	release_num_for_sale,
	release_master_id,
	release_format_quantity,
	release_estimated_weight,
	release_lowest_price,
	release_artists_sort,
	release_country,
	release_notes,
	release_thumb,
	release_title,
	release_date_changed,
	release_status,
	release_released_formatted,
	release_master_url,
	release_released,
	release_date_added,
	release_uri,
	release_resource_url,
	release_data_quality,
	release_community,
	release_community_want,
	release_community_have,
	release_community_status,
	release_community_data_quality,
	release_community_submitter,
	release_community_submitter_username,
	release_community_submitter_resource_url,
	release_community_rating,
	release_community_rating_count,
	release_community_rating_average,
	release_community_contributors,
	release_community_contributors_username,
	release_community_contributors_resource_url,
	release_series,
	release_styles,
	release_genres,
	release_videos,
	release_videos_duration,
	release_videos_embed,
	release_videos_description,
	release_videos_title,
	release_videos_uri,
	release_labels,
	release_labels_id,
	release_labels_name,
	release_labels_entity_type,
	release_labels_catno,
	release_labels_resource_url,
	release_labels_entity_type_name,
	release_artists,
	release_artists_id,
	release_artists_join,
	release_artists_name,
	release_artists_anv,
	release_artists_tracks,
	release_artists_role,
	release_artists_resource_url,
	release_images,
	release_images_height,
	release_images_width,
	release_images_uri,
	release_images_resource_url,
	release_images_type,
	release_images_uri150,
	release_tracklist,
	release_tracklist_duration,
	release_tracklist_position,
	release_tracklist_type_,
	release_tracklist_title,
	release_extraartists,
	release_extraartists_id,
	release_extraartists_join,
	release_extraartists_name,
	release_extraartists_anv,
	release_extraartists_tracks,
	release_extraartists_role,
	release_extraartists_resource_url,
	release_companies,
	release_companies_id,
	release_companies_name,
	release_companies_entity_type,
	release_companies_catno,
	release_companies_resource_url,
	release_companies_entity_type_name,
	release_formats,
	release_formats_name,
	release_formats_qty,
	release_formats_text,
	release_formats_descriptions,
	release_identifiers,
	release_identifiers_type,
	release_identifiers_value,
	release_identifiers_description,
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
	case StateKey::release_year:
		release_.year = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_id:
		release_.id = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_num_for_sale:
		release_.num_for_sale = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_master_id:
		release_.master_id = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_format_quantity:
		release_.format_quantity = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_estimated_weight:
		release_.estimated_weight = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_community_want:
		release_.community_.want = value;
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_have:
		release_.community_.have = value;
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_rating_count:
		release_.community_.rating_.count = value;
		m_state = StateKey::release_community_rating;
		break;
	case StateKey::release_videos_duration:
		release_.videos.back().duration = value;
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_labels_id:
		release_.labels.back().id = value;
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_artists_id:
		release_.artists.back().id = value;
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_images_height:
		release_.images.back().height = value;
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_width:
		release_.images.back().width = value;
		m_state = StateKey::release_images;
		break;
	case StateKey::release_extraartists_id:
		release_.extra_artists.back().id = value;
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_companies_id:
		release_.companies.back().id = value;
		m_state = StateKey::release_companies;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::release_artists_sort:
		release_.artists_sort = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_country:
		release_.country = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_notes:
		release_.notes = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_thumb:
		release_.thumb = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_title:
		release_.title = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_date_changed:
		release_.date_changed = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_status:
		release_.status = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_released_formatted:
		release_.released_formatted = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_master_url:
		release_.master_url = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_released:
		release_.released = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_date_added:
		release_.date_added = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_uri:
		release_.uri = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_resource_url:
		release_.resource_url = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_data_quality:
		release_.data_quality = std::string(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_community_status:
		release_.community_.status = std::string(value, length);
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_data_quality:
		release_.community_.data_quality = std::string(value, length);
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_submitter_username:
		release_.community_.sumbitter_.username = std::string(value, length);
		m_state = StateKey::release_community_submitter;
		break;
	case StateKey::release_community_submitter_resource_url:
		release_.community_.sumbitter_.resource_url = std::string(value, length);
		m_state = StateKey::release_community_submitter;
		break;
	case StateKey::release_community_contributors_username:
		release_.community_.contributors.back().username = std::string(value, length);
		m_state = StateKey::release_community_contributors;
		break;
	case StateKey::release_community_contributors_resource_url:
		release_.community_.contributors.back().resource_url = std::string(value, length);
		m_state = StateKey::release_community_contributors;
		break;
	case StateKey::release_series:
		release_.series.emplace_back(value, length);
		break;
	case StateKey::release_styles:
		release_.styles.emplace_back(value, length);
		break;
	case StateKey::release_genres:
		release_.genres.emplace_back(value, length);
		break;
	case StateKey::release_videos_description:
		release_.videos.back().description = std::string(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_videos_title:
		release_.videos.back().title = std::string(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_videos_uri:
		release_.videos.back().uri = std::string(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_labels_name:
		release_.labels.back().name = std::string(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_entity_type:
		release_.labels.back().entity_type = std::string(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_catno:
		release_.labels.back().catno = std::string(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_resource_url:
		release_.labels.back().resource_url = std::string(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_entity_type_name:
		release_.labels.back().entity_type_name = std::string(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_artists_join:
		release_.artists.back().join = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_name:
		release_.artists.back().name = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_anv:
		release_.artists.back().anv = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_tracks:
		release_.artists.back().tracks = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_role:
		release_.artists.back().role = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_resource_url:
		release_.artists.back().resource_url = std::string(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_images_uri:
		release_.images.back().uri = std::string(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_resource_url:
		release_.images.back().resource_url = std::string(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_type:
		release_.images.back().type = std::string(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_uri150:
		release_.images.back().uri150 = std::string(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_tracklist_duration:
		release_.tracklist.back().duration = std::string(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_position:
		release_.tracklist.back().position = std::string(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_type_:
		release_.tracklist.back().type_ = std::string(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_title:
		release_.tracklist.back().title = std::string(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_extraartists_join:
		release_.extra_artists.back().join = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_name:
		release_.extra_artists.back().name = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_anv:
		release_.extra_artists.back().anv = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_tracks:
		release_.extra_artists.back().tracks = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_role:
		release_.extra_artists.back().role = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_resource_url:
		release_.extra_artists.back().resource_url = std::string(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_companies_name:
		release_.companies.back().name = std::string(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_entity_type:
		release_.companies.back().entity_type = std::string(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_catno:
		release_.companies.back().catno = std::string(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_resource_url:
		release_.companies.back().resource_url = std::string(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_entity_type_name:
		release_.companies.back().entity_type_name = std::string(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_formats_name:
		release_.formats.back().name = std::string(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_qty:
		release_.formats.back().qty = std::string(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_text:
		release_.formats.back().text = std::string(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_descriptions:
		release_.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::release_identifiers_type:
		release_.identifiers.back().type = std::string(value, length);
		m_state = StateKey::release_identifiers;
		break;
	case StateKey::release_identifiers_value:
		release_.identifiers.back().value = std::string(value, length);
		m_state = StateKey::release_identifiers;
		break;
	case StateKey::release_identifiers_description:
		release_.identifiers.back().description = std::string(value, length);
		m_state = StateKey::release_identifiers;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::release_videos_embed:
		release_.videos.back().embed = value;
		m_state = StateKey::release_videos;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::Double(double value)
{
	switch(m_state){
	case StateKey::release_lowest_price:
		release_.lowest_price = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_community_rating_average:
		release_.community_.rating_.average = value;
		m_state = StateKey::release_community_rating;
		break;
	default:
		return false;
	}
	return true;
}
bool super_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::release_community_submitter:
		if(length == 8 && strcmp(str, "username") == 0){
			m_state = StateKey::release_community_submitter_username;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_community_submitter_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community_rating:
		if(length == 5 && strcmp(str, "count") == 0){
			m_state = StateKey::release_community_rating_count;
		}
		else
		if(length == 7 && strcmp(str, "average") == 0){
			m_state = StateKey::release_community_rating_average;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community_contributors:
		if(length == 8 && strcmp(str, "username") == 0){
			m_state = StateKey::release_community_contributors_username;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_community_contributors_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community:
		if(length == 4 && strcmp(str, "want") == 0){
			m_state = StateKey::release_community_want;
		}
		else
		if(length == 4 && strcmp(str, "have") == 0){
			m_state = StateKey::release_community_have;
		}
		else
		if(length == 6 && strcmp(str, "status") == 0){
			m_state = StateKey::release_community_status;
		}
		else
		if(length == 12 && strcmp(str, "data_quality") == 0){
			m_state = StateKey::release_community_data_quality;
		}
		else
		if(length == 9 && strcmp(str, "submitter") == 0){
			m_state = StateKey::release_community_submitter;
		}
		else
		if(length == 6 && strcmp(str, "rating") == 0){
			m_state = StateKey::release_community_rating;
		}
		else
		if(length == 12 && strcmp(str, "contributors") == 0){
			m_state = StateKey::release_community_contributors;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_videos:
		if(length == 8 && strcmp(str, "duration") == 0){
			m_state = StateKey::release_videos_duration;
		}
		else
		if(length == 5 && strcmp(str, "embed") == 0){
			m_state = StateKey::release_videos_embed;
		}
		else
		if(length == 11 && strcmp(str, "description") == 0){
			m_state = StateKey::release_videos_description;
		}
		else
		if(length == 5 && strcmp(str, "title") == 0){
			m_state = StateKey::release_videos_title;
		}
		else
		if(length == 3 && strcmp(str, "uri") == 0){
			m_state = StateKey::release_videos_uri;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_labels:
		if(length == 2 && strcmp(str, "id") == 0){
			m_state = StateKey::release_labels_id;
		}
		else
		if(length == 4 && strcmp(str, "name") == 0){
			m_state = StateKey::release_labels_name;
		}
		else
		if(length == 11 && strcmp(str, "entity_type") == 0){
			m_state = StateKey::release_labels_entity_type;
		}
		else
		if(length == 5 && strcmp(str, "catno") == 0){
			m_state = StateKey::release_labels_catno;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_labels_resource_url;
		}
		else
		if(length == 16 && strcmp(str, "entity_type_name") == 0){
			m_state = StateKey::release_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_artists:
		if(length == 2 && strcmp(str, "id") == 0){
			m_state = StateKey::release_artists_id;
		}
		else
		if(length == 4 && strcmp(str, "join") == 0){
			m_state = StateKey::release_artists_join;
		}
		else
		if(length == 4 && strcmp(str, "name") == 0){
			m_state = StateKey::release_artists_name;
		}
		else
		if(length == 3 && strcmp(str, "anv") == 0){
			m_state = StateKey::release_artists_anv;
		}
		else
		if(length == 6 && strcmp(str, "tracks") == 0){
			m_state = StateKey::release_artists_tracks;
		}
		else
		if(length == 4 && strcmp(str, "role") == 0){
			m_state = StateKey::release_artists_role;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_images:
		if(length == 6 && strcmp(str, "height") == 0){
			m_state = StateKey::release_images_height;
		}
		else
		if(length == 5 && strcmp(str, "width") == 0){
			m_state = StateKey::release_images_width;
		}
		else
		if(length == 3 && strcmp(str, "uri") == 0){
			m_state = StateKey::release_images_uri;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_images_resource_url;
		}
		else
		if(length == 4 && strcmp(str, "type") == 0){
			m_state = StateKey::release_images_type;
		}
		else
		if(length == 6 && strcmp(str, "uri150") == 0){
			m_state = StateKey::release_images_uri150;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_tracklist:
		if(length == 8 && strcmp(str, "duration") == 0){
			m_state = StateKey::release_tracklist_duration;
		}
		else
		if(length == 8 && strcmp(str, "position") == 0){
			m_state = StateKey::release_tracklist_position;
		}
		else
		if(length == 5 && strcmp(str, "type_") == 0){
			m_state = StateKey::release_tracklist_type_;
		}
		else
		if(length == 5 && strcmp(str, "title") == 0){
			m_state = StateKey::release_tracklist_title;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_extraartists:
		if(length == 2 && strcmp(str, "id") == 0){
			m_state = StateKey::release_extraartists_id;
		}
		else
		if(length == 4 && strcmp(str, "join") == 0){
			m_state = StateKey::release_extraartists_join;
		}
		else
		if(length == 4 && strcmp(str, "name") == 0){
			m_state = StateKey::release_extraartists_name;
		}
		else
		if(length == 3 && strcmp(str, "anv") == 0){
			m_state = StateKey::release_extraartists_anv;
		}
		else
		if(length == 6 && strcmp(str, "tracks") == 0){
			m_state = StateKey::release_extraartists_tracks;
		}
		else
		if(length == 4 && strcmp(str, "role") == 0){
			m_state = StateKey::release_extraartists_role;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_extraartists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_companies:
		if(length == 2 && strcmp(str, "id") == 0){
			m_state = StateKey::release_companies_id;
		}
		else
		if(length == 4 && strcmp(str, "name") == 0){
			m_state = StateKey::release_companies_name;
		}
		else
		if(length == 11 && strcmp(str, "entity_type") == 0){
			m_state = StateKey::release_companies_entity_type;
		}
		else
		if(length == 5 && strcmp(str, "catno") == 0){
			m_state = StateKey::release_companies_catno;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_companies_resource_url;
		}
		else
		if(length == 16 && strcmp(str, "entity_type_name") == 0){
			m_state = StateKey::release_companies_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_formats:
		if(length == 4 && strcmp(str, "name") == 0){
			m_state = StateKey::release_formats_name;
		}
		else
		if(length == 3 && strcmp(str, "qty") == 0){
			m_state = StateKey::release_formats_qty;
		}
		else
		if(length == 4 && strcmp(str, "text") == 0){
			m_state = StateKey::release_formats_text;
		}
		else
		if(length == 12 && strcmp(str, "descriptions") == 0){
			m_state = StateKey::release_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_identifiers:
		if(length == 4 && strcmp(str, "type") == 0){
			m_state = StateKey::release_identifiers_type;
		}
		else
		if(length == 5 && strcmp(str, "value") == 0){
			m_state = StateKey::release_identifiers_value;
		}
		else
		if(length == 11 && strcmp(str, "description") == 0){
			m_state = StateKey::release_identifiers_description;
		}
		else {
			return false;
		}
		break;
	case StateKey::release:
		if(length == 4 && strcmp(str, "year") == 0){
			m_state = StateKey::release_year;
		}
		else
		if(length == 2 && strcmp(str, "id") == 0){
			m_state = StateKey::release_id;
		}
		else
		if(length == 12 && strcmp(str, "num_for_sale") == 0){
			m_state = StateKey::release_num_for_sale;
		}
		else
		if(length == 9 && strcmp(str, "master_id") == 0){
			m_state = StateKey::release_master_id;
		}
		else
		if(length == 15 && strcmp(str, "format_quantity") == 0){
			m_state = StateKey::release_format_quantity;
		}
		else
		if(length == 16 && strcmp(str, "estimated_weight") == 0){
			m_state = StateKey::release_estimated_weight;
		}
		else
		if(length == 12 && strcmp(str, "lowest_price") == 0){
			m_state = StateKey::release_lowest_price;
		}
		else
		if(length == 12 && strcmp(str, "artists_sort") == 0){
			m_state = StateKey::release_artists_sort;
		}
		else
		if(length == 7 && strcmp(str, "country") == 0){
			m_state = StateKey::release_country;
		}
		else
		if(length == 5 && strcmp(str, "notes") == 0){
			m_state = StateKey::release_notes;
		}
		else
		if(length == 5 && strcmp(str, "thumb") == 0){
			m_state = StateKey::release_thumb;
		}
		else
		if(length == 5 && strcmp(str, "title") == 0){
			m_state = StateKey::release_title;
		}
		else
		if(length == 12 && strcmp(str, "date_changed") == 0){
			m_state = StateKey::release_date_changed;
		}
		else
		if(length == 6 && strcmp(str, "status") == 0){
			m_state = StateKey::release_status;
		}
		else
		if(length == 18 && strcmp(str, "released_formatted") == 0){
			m_state = StateKey::release_released_formatted;
		}
		else
		if(length == 10 && strcmp(str, "master_url") == 0){
			m_state = StateKey::release_master_url;
		}
		else
		if(length == 8 && strcmp(str, "released") == 0){
			m_state = StateKey::release_released;
		}
		else
		if(length == 10 && strcmp(str, "date_added") == 0){
			m_state = StateKey::release_date_added;
		}
		else
		if(length == 3 && strcmp(str, "uri") == 0){
			m_state = StateKey::release_uri;
		}
		else
		if(length == 12 && strcmp(str, "resource_url") == 0){
			m_state = StateKey::release_resource_url;
		}
		else
		if(length == 12 && strcmp(str, "data_quality") == 0){
			m_state = StateKey::release_data_quality;
		}
		else
		if(length == 9 && strcmp(str, "community") == 0){
			m_state = StateKey::release_community;
		}
		else
		if(length == 6 && strcmp(str, "series") == 0){
			m_state = StateKey::release_series;
		}
		else
		if(length == 6 && strcmp(str, "styles") == 0){
			m_state = StateKey::release_styles;
		}
		else
		if(length == 6 && strcmp(str, "genres") == 0){
			m_state = StateKey::release_genres;
		}
		else
		if(length == 6 && strcmp(str, "videos") == 0){
			m_state = StateKey::release_videos;
		}
		else
		if(length == 6 && strcmp(str, "labels") == 0){
			m_state = StateKey::release_labels;
		}
		else
		if(length == 7 && strcmp(str, "artists") == 0){
			m_state = StateKey::release_artists;
		}
		else
		if(length == 6 && strcmp(str, "images") == 0){
			m_state = StateKey::release_images;
		}
		else
		if(length == 9 && strcmp(str, "tracklist") == 0){
			m_state = StateKey::release_tracklist;
		}
		else
		if(length == 12 && strcmp(str, "extraartists") == 0){
			m_state = StateKey::release_extraartists;
		}
		else
		if(length == 9 && strcmp(str, "companies") == 0){
			m_state = StateKey::release_companies;
		}
		else
		if(length == 7 && strcmp(str, "formats") == 0){
			m_state = StateKey::release_formats;
		}
		else
		if(length == 11 && strcmp(str, "identifiers") == 0){
			m_state = StateKey::release_identifiers;
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
	case StateKey::release_community_contributors:
		release_.community_.contributors.emplace_back();
		break;
	case StateKey::release_videos:
		release_.videos.emplace_back();
		break;
	case StateKey::release_labels:
		release_.labels.emplace_back();
		break;
	case StateKey::release_artists:
		release_.artists.emplace_back();
		break;
	case StateKey::release_images:
		release_.images.emplace_back();
		break;
	case StateKey::release_tracklist:
		release_.tracklist.emplace_back();
		break;
	case StateKey::release_extraartists:
		release_.extra_artists.emplace_back();
		break;
	case StateKey::release_companies:
		release_.companies.emplace_back();
		break;
	case StateKey::release_formats:
		release_.formats.emplace_back();
		break;
	case StateKey::release_identifiers:
		release_.identifiers.emplace_back();
		break;
	}
	return true;
}

bool super_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::release_community_contributors:
		m_state = StateKey::release_community;
		break;
	case StateKey::release_series:
		m_state = StateKey::release;
		break;
	case StateKey::release_styles:
		m_state = StateKey::release;
		break;
	case StateKey::release_genres:
		m_state = StateKey::release;
		break;
	case StateKey::release_videos:
		m_state = StateKey::release;
		break;
	case StateKey::release_labels:
		m_state = StateKey::release;
		break;
	case StateKey::release_artists:
		m_state = StateKey::release;
		break;
	case StateKey::release_images:
		m_state = StateKey::release;
		break;
	case StateKey::release_tracklist:
		m_state = StateKey::release;
		break;
	case StateKey::release_extraartists:
		m_state = StateKey::release;
		break;
	case StateKey::release_companies:
		m_state = StateKey::release;
		break;
	case StateKey::release_formats:
		m_state = StateKey::release;
		break;
	case StateKey::release_formats_descriptions:
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_identifiers:
		m_state = StateKey::release;
		break;
	}
	return true;
}

bool super_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::release_community:
		m_state = StateKey::release;
		break;
	case StateKey::release_community_submitter:
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_rating:
		m_state = StateKey::release_community;
		break;
	}
	return true;
}

super_parser::super_parser()
{
	m_state = StateKey::release;
}

} // namespace discogs
} // namespace parser
} // namespace release
