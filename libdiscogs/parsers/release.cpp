/* clang-format off */
#include "release_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

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
	release_series_id,
	release_series_name,
	release_series_entity_type,
	release_series_catno,
	release_series_resource_url,
	release_series_entity_type_name,
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
	release_tracklist_artists,
	release_tracklist_artists_id,
	release_tracklist_artists_join,
	release_tracklist_artists_name,
	release_tracklist_artists_anv,
	release_tracklist_artists_tracks,
	release_tracklist_artists_role,
	release_tracklist_artists_resource_url,
	release_tracklist_extraartists,
	release_tracklist_extraartists_id,
	release_tracklist_extraartists_join,
	release_tracklist_extraartists_name,
	release_tracklist_extraartists_anv,
	release_tracklist_extraartists_tracks,
	release_tracklist_extraartists_role,
	release_tracklist_extraartists_resource_url,
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

bool release_parser::Int(int value)
{
	return Number((int)value);
}

bool release_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool release_parser::Int64(int64_t i)
{
	return false;
}

bool release_parser::Uint64(uint64_t i)
{
	return false;
}
bool release_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::release_artists_sort:
		RESULT.artists_sort = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_country:
		RESULT.country = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_notes:
		RESULT.notes = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_thumb:
		RESULT.thumb = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_title:
		RESULT.title = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_date_changed:
		RESULT.date_changed = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_status:
		RESULT.status = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_released_formatted:
		RESULT.released_formatted = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_master_url:
		RESULT.master_url = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_released:
		RESULT.released = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_date_added:
		RESULT.date_added = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_uri:
		RESULT.uri = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_resource_url:
		RESULT.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_data_quality:
		RESULT.data_quality = ::platform::string_t(value, length);
		m_state = StateKey::release;
		break;
	case StateKey::release_community_status:
		RESULT.community_.status = ::platform::string_t(value, length);
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_data_quality:
		RESULT.community_.data_quality = ::platform::string_t(value, length);
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_submitter_username:
		RESULT.community_.sumbitter_.username = ::platform::string_t(value, length);
		m_state = StateKey::release_community_submitter;
		break;
	case StateKey::release_community_submitter_resource_url:
		RESULT.community_.sumbitter_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_community_submitter;
		break;
	case StateKey::release_community_contributors_username:
		RESULT.community_.contributors.back().username = ::platform::string_t(value, length);
		m_state = StateKey::release_community_contributors;
		break;
	case StateKey::release_community_contributors_resource_url:
		RESULT.community_.contributors.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_community_contributors;
		break;
	case StateKey::release_series_name:
		RESULT.series_.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_series;
		break;
	case StateKey::release_series_entity_type:
		RESULT.series_.back().entity_type = ::platform::string_t(value, length);
		m_state = StateKey::release_series;
		break;
	case StateKey::release_series_catno:
		RESULT.series_.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::release_series;
		break;
	case StateKey::release_series_resource_url:
		RESULT.series_.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_series;
		break;
	case StateKey::release_series_entity_type_name:
		RESULT.series_.back().entity_type_name = ::platform::string_t(value, length);
		m_state = StateKey::release_series;
		break;
	case StateKey::release_styles:
		RESULT.styles.emplace_back(value, length);
		break;
	case StateKey::release_genres:
		RESULT.genres.emplace_back(value, length);
		break;
	case StateKey::release_videos_description:
		RESULT.videos.back().description = ::platform::string_t(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_videos_title:
		RESULT.videos.back().title = ::platform::string_t(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_videos_uri:
		RESULT.videos.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_labels_name:
		RESULT.labels.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_entity_type:
		RESULT.labels.back().entity_type = ::platform::string_t(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_catno:
		RESULT.labels.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_resource_url:
		RESULT.labels.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_labels_entity_type_name:
		RESULT.labels.back().entity_type_name = ::platform::string_t(value, length);
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_artists_join:
		RESULT.artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_name:
		RESULT.artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_anv:
		RESULT.artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_tracks:
		RESULT.artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_role:
		RESULT.artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_artists_resource_url:
		RESULT.artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_images_uri:
		RESULT.images.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_resource_url:
		RESULT.images.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_type:
		RESULT.images.back().type = ::platform::string_t(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_uri150:
		RESULT.images.back().uri150 = ::platform::string_t(value, length);
		m_state = StateKey::release_images;
		break;
	case StateKey::release_tracklist_duration:
		RESULT.tracklist.back().duration = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_position:
		RESULT.tracklist.back().position = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_type_:
		RESULT.tracklist.back().type_ = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_title:
		RESULT.tracklist.back().title = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_artists_join:
		RESULT.tracklist.back().artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_artists_name:
		RESULT.tracklist.back().artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_artists_anv:
		RESULT.tracklist.back().artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_artists_tracks:
		RESULT.tracklist.back().artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_artists_role:
		RESULT.tracklist.back().artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_artists_resource_url:
		RESULT.tracklist.back().artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_extraartists_join:
		RESULT.tracklist.back().extraartists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_tracklist_extraartists_name:
		RESULT.tracklist.back().extraartists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_tracklist_extraartists_anv:
		RESULT.tracklist.back().extraartists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_tracklist_extraartists_tracks:
		RESULT.tracklist.back().extraartists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_tracklist_extraartists_role:
		RESULT.tracklist.back().extraartists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_tracklist_extraartists_resource_url:
		RESULT.tracklist.back().extraartists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_extraartists_join:
		RESULT.extra_artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_name:
		RESULT.extra_artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_anv:
		RESULT.extra_artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_tracks:
		RESULT.extra_artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_role:
		RESULT.extra_artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_extraartists_resource_url:
		RESULT.extra_artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_companies_name:
		RESULT.companies.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_entity_type:
		RESULT.companies.back().entity_type = ::platform::string_t(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_catno:
		RESULT.companies.back().catno = ::platform::string_t(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_resource_url:
		RESULT.companies.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_companies_entity_type_name:
		RESULT.companies.back().entity_type_name = ::platform::string_t(value, length);
		m_state = StateKey::release_companies;
		break;
	case StateKey::release_formats_name:
		RESULT.formats.back().name = ::platform::string_t(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_qty:
		RESULT.formats.back().qty = ::platform::string_t(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_text:
		RESULT.formats.back().text = ::platform::string_t(value, length);
		m_state = StateKey::release_formats;
		break;
	case StateKey::release_formats_descriptions:
		RESULT.formats.back().descriptions.emplace_back(value, length);
		break;
	case StateKey::release_identifiers_type:
		RESULT.identifiers.back().type = ::platform::string_t(value, length);
		m_state = StateKey::release_identifiers;
		break;
	case StateKey::release_identifiers_value:
		RESULT.identifiers.back().value = ::platform::string_t(value, length);
		m_state = StateKey::release_identifiers;
		break;
	case StateKey::release_identifiers_description:
		RESULT.identifiers.back().description = ::platform::string_t(value, length);
		m_state = StateKey::release_identifiers;
		break;
	default:
		return false;
	}
	return true;
}
bool release_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::release_videos_embed:
		RESULT.videos.back().embed = value;
		m_state = StateKey::release_videos;
		break;
	default:
		return false;
	}
	return true;
}
bool release_parser::Double(double value)
{
	switch(m_state){
	case StateKey::release_lowest_price:
		RESULT.lowest_price = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_community_rating_average:
		RESULT.community_.rating_.average = value;
		m_state = StateKey::release_community_rating;
		break;
	default:
		return false;
	}
	return true;
}
bool release_parser::Number(int value)
{
	switch(m_state){
	case StateKey::release_year:
		RESULT.year = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_id:
		RESULT.id = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_num_for_sale:
		RESULT.num_for_sale = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_master_id:
		RESULT.master_id = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_format_quantity:
		RESULT.format_quantity = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_estimated_weight:
		RESULT.estimated_weight = value;
		m_state = StateKey::release;
		break;
	case StateKey::release_community_want:
		RESULT.community_.want = value;
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_have:
		RESULT.community_.have = value;
		m_state = StateKey::release_community;
		break;
	case StateKey::release_community_rating_count:
		RESULT.community_.rating_.count = value;
		m_state = StateKey::release_community_rating;
		break;
	case StateKey::release_series_id:
		RESULT.series_.back().id = value;
		m_state = StateKey::release_series;
		break;
	case StateKey::release_videos_duration:
		RESULT.videos.back().duration = value;
		m_state = StateKey::release_videos;
		break;
	case StateKey::release_labels_id:
		RESULT.labels.back().id = value;
		m_state = StateKey::release_labels;
		break;
	case StateKey::release_artists_id:
		RESULT.artists.back().id = value;
		m_state = StateKey::release_artists;
		break;
	case StateKey::release_images_height:
		RESULT.images.back().height = value;
		m_state = StateKey::release_images;
		break;
	case StateKey::release_images_width:
		RESULT.images.back().width = value;
		m_state = StateKey::release_images;
		break;
	case StateKey::release_tracklist_artists_id:
		RESULT.tracklist.back().artists.back().id = value;
		m_state = StateKey::release_tracklist_artists;
		break;
	case StateKey::release_tracklist_extraartists_id:
		RESULT.tracklist.back().extraartists.back().id = value;
		m_state = StateKey::release_tracklist_extraartists;
		break;
	case StateKey::release_extraartists_id:
		RESULT.extra_artists.back().id = value;
		m_state = StateKey::release_extraartists;
		break;
	case StateKey::release_companies_id:
		RESULT.companies.back().id = value;
		m_state = StateKey::release_companies;
		break;
	default:
		return false;
	}
	return true;
}
bool release_parser::RawNumber(const Ch*, rapidjson::SizeType, bool)
{
	return false;
}

bool release_parser::Null()
{
	switch(m_state){
		case StateKey::release_year:
			m_state = StateKey::release;
			break;
		case StateKey::release_id:
			m_state = StateKey::release;
			break;
		case StateKey::release_num_for_sale:
			m_state = StateKey::release;
			break;
		case StateKey::release_master_id:
			m_state = StateKey::release;
			break;
		case StateKey::release_format_quantity:
			m_state = StateKey::release;
			break;
		case StateKey::release_estimated_weight:
			m_state = StateKey::release;
			break;
		case StateKey::release_lowest_price:
			m_state = StateKey::release;
			break;
		case StateKey::release_artists_sort:
			m_state = StateKey::release;
			break;
		case StateKey::release_country:
			m_state = StateKey::release;
			break;
		case StateKey::release_notes:
			m_state = StateKey::release;
			break;
		case StateKey::release_thumb:
			m_state = StateKey::release;
			break;
		case StateKey::release_title:
			m_state = StateKey::release;
			break;
		case StateKey::release_date_changed:
			m_state = StateKey::release;
			break;
		case StateKey::release_status:
			m_state = StateKey::release;
			break;
		case StateKey::release_released_formatted:
			m_state = StateKey::release;
			break;
		case StateKey::release_master_url:
			m_state = StateKey::release;
			break;
		case StateKey::release_released:
			m_state = StateKey::release;
			break;
		case StateKey::release_date_added:
			m_state = StateKey::release;
			break;
		case StateKey::release_uri:
			m_state = StateKey::release;
			break;
		case StateKey::release_resource_url:
			m_state = StateKey::release;
			break;
		case StateKey::release_data_quality:
			m_state = StateKey::release;
			break;
		case StateKey::release_community:
			m_state = StateKey::release;
			break;
		case StateKey::release_community_want:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_have:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_status:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_data_quality:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_submitter:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_submitter_username:
			m_state = StateKey::release_community_submitter;
			break;
		case StateKey::release_community_submitter_resource_url:
			m_state = StateKey::release_community_submitter;
			break;
		case StateKey::release_community_rating:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_rating_count:
			m_state = StateKey::release_community_rating;
			break;
		case StateKey::release_community_rating_average:
			m_state = StateKey::release_community_rating;
			break;
		case StateKey::release_community_contributors:
			m_state = StateKey::release_community;
			break;
		case StateKey::release_community_contributors_username:
			m_state = StateKey::release_community_contributors;
			break;
		case StateKey::release_community_contributors_resource_url:
			m_state = StateKey::release_community_contributors;
			break;
		case StateKey::release_series:
			m_state = StateKey::release;
			break;
		case StateKey::release_series_id:
			m_state = StateKey::release_series;
			break;
		case StateKey::release_series_name:
			m_state = StateKey::release_series;
			break;
		case StateKey::release_series_entity_type:
			m_state = StateKey::release_series;
			break;
		case StateKey::release_series_catno:
			m_state = StateKey::release_series;
			break;
		case StateKey::release_series_resource_url:
			m_state = StateKey::release_series;
			break;
		case StateKey::release_series_entity_type_name:
			m_state = StateKey::release_series;
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
		case StateKey::release_videos_duration:
			m_state = StateKey::release_videos;
			break;
		case StateKey::release_videos_embed:
			m_state = StateKey::release_videos;
			break;
		case StateKey::release_videos_description:
			m_state = StateKey::release_videos;
			break;
		case StateKey::release_videos_title:
			m_state = StateKey::release_videos;
			break;
		case StateKey::release_videos_uri:
			m_state = StateKey::release_videos;
			break;
		case StateKey::release_labels:
			m_state = StateKey::release;
			break;
		case StateKey::release_labels_id:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_labels_name:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_labels_entity_type:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_labels_catno:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_labels_resource_url:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_labels_entity_type_name:
			m_state = StateKey::release_labels;
			break;
		case StateKey::release_artists:
			m_state = StateKey::release;
			break;
		case StateKey::release_artists_id:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_join:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_name:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_anv:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_tracks:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_role:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_artists_resource_url:
			m_state = StateKey::release_artists;
			break;
		case StateKey::release_images:
			m_state = StateKey::release;
			break;
		case StateKey::release_images_height:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_images_width:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_images_uri:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_images_resource_url:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_images_type:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_images_uri150:
			m_state = StateKey::release_images;
			break;
		case StateKey::release_tracklist:
			m_state = StateKey::release;
			break;
		case StateKey::release_tracklist_duration:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_position:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_type_:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_title:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_artists:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_artists_id:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_join:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_name:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_anv:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_tracks:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_role:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_artists_resource_url:
			m_state = StateKey::release_tracklist_artists;
			break;
		case StateKey::release_tracklist_extraartists:
			m_state = StateKey::release_tracklist;
			break;
		case StateKey::release_tracklist_extraartists_id:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_join:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_name:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_anv:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_tracks:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_role:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_tracklist_extraartists_resource_url:
			m_state = StateKey::release_tracklist_extraartists;
			break;
		case StateKey::release_extraartists:
			m_state = StateKey::release;
			break;
		case StateKey::release_extraartists_id:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_join:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_name:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_anv:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_tracks:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_role:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_extraartists_resource_url:
			m_state = StateKey::release_extraartists;
			break;
		case StateKey::release_companies:
			m_state = StateKey::release;
			break;
		case StateKey::release_companies_id:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_companies_name:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_companies_entity_type:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_companies_catno:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_companies_resource_url:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_companies_entity_type_name:
			m_state = StateKey::release_companies;
			break;
		case StateKey::release_formats:
			m_state = StateKey::release;
			break;
		case StateKey::release_formats_name:
			m_state = StateKey::release_formats;
			break;
		case StateKey::release_formats_qty:
			m_state = StateKey::release_formats;
			break;
		case StateKey::release_formats_text:
			m_state = StateKey::release_formats;
			break;
		case StateKey::release_formats_descriptions:
			m_state = StateKey::release_formats;
			break;
		case StateKey::release_identifiers:
			m_state = StateKey::release;
			break;
		case StateKey::release_identifiers_type:
			m_state = StateKey::release_identifiers;
			break;
		case StateKey::release_identifiers_value:
			m_state = StateKey::release_identifiers;
			break;
		case StateKey::release_identifiers_description:
			m_state = StateKey::release_identifiers;
			break;
	}
	return true;
}
bool release_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::release_community_submitter:
		if(length == 8 && platform::strcmp(str, STR("username")) == 0){
			m_state = StateKey::release_community_submitter_username;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_community_submitter_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community_rating:
		if(length == 5 && platform::strcmp(str, STR("count")) == 0){
			m_state = StateKey::release_community_rating_count;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("average")) == 0){
			m_state = StateKey::release_community_rating_average;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community_contributors:
		if(length == 8 && platform::strcmp(str, STR("username")) == 0){
			m_state = StateKey::release_community_contributors_username;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_community_contributors_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_community:
		if(length == 4 && platform::strcmp(str, STR("want")) == 0){
			m_state = StateKey::release_community_want;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("have")) == 0){
			m_state = StateKey::release_community_have;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("status")) == 0){
			m_state = StateKey::release_community_status;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("data_quality")) == 0){
			m_state = StateKey::release_community_data_quality;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("submitter")) == 0){
			m_state = StateKey::release_community_submitter;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::release_community_rating;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("contributors")) == 0){
			m_state = StateKey::release_community_contributors;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_series:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_series_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_series_name;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::release_series_entity_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::release_series_catno;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_series_resource_url;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::release_series_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_videos:
		if(length == 8 && platform::strcmp(str, STR("duration")) == 0){
			m_state = StateKey::release_videos_duration;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("embed")) == 0){
			m_state = StateKey::release_videos_embed;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("description")) == 0){
			m_state = StateKey::release_videos_description;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::release_videos_title;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::release_videos_uri;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_labels:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_labels_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_labels_name;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::release_labels_entity_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::release_labels_catno;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_labels_resource_url;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::release_labels_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::release_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::release_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::release_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::release_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_images:
		if(length == 6 && platform::strcmp(str, STR("height")) == 0){
			m_state = StateKey::release_images_height;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("width")) == 0){
			m_state = StateKey::release_images_width;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::release_images_uri;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_images_resource_url;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::release_images_type;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("uri150")) == 0){
			m_state = StateKey::release_images_uri150;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_tracklist_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_tracklist_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::release_tracklist_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_tracklist_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::release_tracklist_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::release_tracklist_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::release_tracklist_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_tracklist_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_tracklist_extraartists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_tracklist_extraartists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::release_tracklist_extraartists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_tracklist_extraartists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::release_tracklist_extraartists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::release_tracklist_extraartists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::release_tracklist_extraartists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_tracklist_extraartists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_tracklist:
		if(length == 8 && platform::strcmp(str, STR("duration")) == 0){
			m_state = StateKey::release_tracklist_duration;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("position")) == 0){
			m_state = StateKey::release_tracklist_position;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("type_")) == 0){
			m_state = StateKey::release_tracklist_type_;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::release_tracklist_title;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::release_tracklist_artists;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("extraartists")) == 0){
			m_state = StateKey::release_tracklist_extraartists;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_extraartists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_extraartists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::release_extraartists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_extraartists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::release_extraartists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::release_extraartists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::release_extraartists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_extraartists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_companies:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_companies_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_companies_name;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("entity_type")) == 0){
			m_state = StateKey::release_companies_entity_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("catno")) == 0){
			m_state = StateKey::release_companies_catno;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_companies_resource_url;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("entity_type_name")) == 0){
			m_state = StateKey::release_companies_entity_type_name;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_formats:
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::release_formats_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("qty")) == 0){
			m_state = StateKey::release_formats_qty;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("text")) == 0){
			m_state = StateKey::release_formats_text;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("descriptions")) == 0){
			m_state = StateKey::release_formats_descriptions;
		}
		else {
			return false;
		}
		break;
	case StateKey::release_identifiers:
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::release_identifiers_type;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::release_identifiers_value;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("description")) == 0){
			m_state = StateKey::release_identifiers_description;
		}
		else {
			return false;
		}
		break;
	case StateKey::release:
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::release_year;
		}
		else
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::release_id;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("num_for_sale")) == 0){
			m_state = StateKey::release_num_for_sale;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("master_id")) == 0){
			m_state = StateKey::release_master_id;
		}
		else
		if(length == 15 && platform::strcmp(str, STR("format_quantity")) == 0){
			m_state = StateKey::release_format_quantity;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("estimated_weight")) == 0){
			m_state = StateKey::release_estimated_weight;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("lowest_price")) == 0){
			m_state = StateKey::release_lowest_price;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("artists_sort")) == 0){
			m_state = StateKey::release_artists_sort;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("country")) == 0){
			m_state = StateKey::release_country;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("notes")) == 0){
			m_state = StateKey::release_notes;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("thumb")) == 0){
			m_state = StateKey::release_thumb;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::release_title;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("date_changed")) == 0){
			m_state = StateKey::release_date_changed;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("status")) == 0){
			m_state = StateKey::release_status;
		}
		else
		if(length == 18 && platform::strcmp(str, STR("released_formatted")) == 0){
			m_state = StateKey::release_released_formatted;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("master_url")) == 0){
			m_state = StateKey::release_master_url;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("released")) == 0){
			m_state = StateKey::release_released;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("date_added")) == 0){
			m_state = StateKey::release_date_added;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::release_uri;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::release_resource_url;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("data_quality")) == 0){
			m_state = StateKey::release_data_quality;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("community")) == 0){
			m_state = StateKey::release_community;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("series")) == 0){
			m_state = StateKey::release_series;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("styles")) == 0){
			m_state = StateKey::release_styles;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("genres")) == 0){
			m_state = StateKey::release_genres;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("videos")) == 0){
			m_state = StateKey::release_videos;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("labels")) == 0){
			m_state = StateKey::release_labels;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::release_artists;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("images")) == 0){
			m_state = StateKey::release_images;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("tracklist")) == 0){
			m_state = StateKey::release_tracklist;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("extraartists")) == 0){
			m_state = StateKey::release_extraartists;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("companies")) == 0){
			m_state = StateKey::release_companies;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("formats")) == 0){
			m_state = StateKey::release_formats;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("identifiers")) == 0){
			m_state = StateKey::release_identifiers;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool release_parser::StartArray()
{
	return true;
}
bool release_parser::EndArray(rapidjson::SizeType memberCount)
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
	case StateKey::release_tracklist_artists:
		m_state = StateKey::release_tracklist;
		break;
	case StateKey::release_tracklist_extraartists:
		m_state = StateKey::release_tracklist;
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

bool release_parser::StartObject()
{
	switch(m_state){
	case StateKey::release_community_contributors:
		RESULT.community_.contributors.emplace_back();
		break;
	case StateKey::release_series:
		RESULT.series_.emplace_back();
		break;
	case StateKey::release_videos:
		RESULT.videos.emplace_back();
		break;
	case StateKey::release_labels:
		RESULT.labels.emplace_back();
		break;
	case StateKey::release_artists:
		RESULT.artists.emplace_back();
		break;
	case StateKey::release_images:
		RESULT.images.emplace_back();
		break;
	case StateKey::release_tracklist:
		RESULT.tracklist.emplace_back();
		break;
	case StateKey::release_tracklist_artists:
		RESULT.tracklist.back().artists.emplace_back();
		break;
	case StateKey::release_tracklist_extraartists:
		RESULT.tracklist.back().extraartists.emplace_back();
		break;
	case StateKey::release_extraartists:
		RESULT.extra_artists.emplace_back();
		break;
	case StateKey::release_companies:
		RESULT.companies.emplace_back();
		break;
	case StateKey::release_formats:
		RESULT.formats.emplace_back();
		break;
	case StateKey::release_identifiers:
		RESULT.identifiers.emplace_back();
		break;
	}
	return true;
}

bool release_parser::EndObject(rapidjson::SizeType memberCount)
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

release_parser::release_parser()
{
	m_state = StateKey::release;
}

} // namespace discogs
} // namespace parser
