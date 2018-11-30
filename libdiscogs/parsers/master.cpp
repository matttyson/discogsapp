/* clang-format off */
#include "master_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace result {

enum class StateKey {
	master,
	master_id,
	master_year,
	master_num_for_sale,
	master_main_release,
	master_lowest_price,
	master_uri,
	master_title,
	master_versions_url,
	master_resource_url,
	master_data_quality,
	master_main_release_url,
	master_styles,
	master_genres,
	master_images,
	master_images_height,
	master_images_width,
	master_images_uri,
	master_images_resource_url,
	master_images_type,
	master_images_uri150,
	master_videos,
	master_videos_duration,
	master_videos_embed,
	master_videos_description,
	master_videos_title,
	master_videos_uri,
	master_artists,
	master_artists_id,
	master_artists_join,
	master_artists_name,
	master_artists_anv,
	master_artists_tracks,
	master_artists_role,
	master_artists_resource_url,
	master_tracklist,
	master_tracklist_duration,
	master_tracklist_position,
	master_tracklist_type_,
	master_tracklist_title,
	master_tracklist_artists,
	master_tracklist_artists_id,
	master_tracklist_artists_join,
	master_tracklist_artists_name,
	master_tracklist_artists_anv,
	master_tracklist_artists_tracks,
	master_tracklist_artists_role,
	master_tracklist_artists_resource_url,
	master_tracklist_extraartists,
	master_tracklist_extraartists_id,
	master_tracklist_extraartists_join,
	master_tracklist_extraartists_name,
	master_tracklist_extraartists_anv,
	master_tracklist_extraartists_tracks,
	master_tracklist_extraartists_role,
	master_tracklist_extraartists_resource_url,
};

bool master_parser::Int(int value)
{
	return Number((int)value);
}

bool master_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool master_parser::Int64(int64_t i)
{
	return false;
}

bool master_parser::Uint64(uint64_t i)
{
	return false;
}
bool master_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::master_uri:
		RESULT.uri = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_title:
		RESULT.title = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_versions_url:
		RESULT.versions_url = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_resource_url:
		RESULT.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_data_quality:
		RESULT.data_quality = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_main_release_url:
		RESULT.main_release_url = ::platform::string_t(value, length);
		m_state = StateKey::master;
		break;
	case StateKey::master_styles:
		RESULT.styles.emplace_back(value, length);
		break;
	case StateKey::master_genres:
		RESULT.genres.emplace_back(value, length);
		break;
	case StateKey::master_images_uri:
		RESULT.images.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::master_images;
		break;
	case StateKey::master_images_resource_url:
		RESULT.images.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::master_images;
		break;
	case StateKey::master_images_type:
		RESULT.images.back().type = ::platform::string_t(value, length);
		m_state = StateKey::master_images;
		break;
	case StateKey::master_images_uri150:
		RESULT.images.back().uri150 = ::platform::string_t(value, length);
		m_state = StateKey::master_images;
		break;
	case StateKey::master_videos_description:
		RESULT.videos.back().description = ::platform::string_t(value, length);
		m_state = StateKey::master_videos;
		break;
	case StateKey::master_videos_title:
		RESULT.videos.back().title = ::platform::string_t(value, length);
		m_state = StateKey::master_videos;
		break;
	case StateKey::master_videos_uri:
		RESULT.videos.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::master_videos;
		break;
	case StateKey::master_artists_join:
		RESULT.artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_artists_name:
		RESULT.artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_artists_anv:
		RESULT.artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_artists_tracks:
		RESULT.artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_artists_role:
		RESULT.artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_artists_resource_url:
		RESULT.artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_tracklist_duration:
		RESULT.tracklist.back().duration = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist;
		break;
	case StateKey::master_tracklist_position:
		RESULT.tracklist.back().position = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist;
		break;
	case StateKey::master_tracklist_type_:
		RESULT.tracklist.back().type_ = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist;
		break;
	case StateKey::master_tracklist_title:
		RESULT.tracklist.back().title = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist;
		break;
	case StateKey::master_tracklist_artists_join:
		RESULT.tracklist.back().artists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_artists_name:
		RESULT.tracklist.back().artists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_artists_anv:
		RESULT.tracklist.back().artists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_artists_tracks:
		RESULT.tracklist.back().artists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_artists_role:
		RESULT.tracklist.back().artists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_artists_resource_url:
		RESULT.tracklist.back().artists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_extraartists_join:
		RESULT.tracklist.back().extraartists.back().join = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	case StateKey::master_tracklist_extraartists_name:
		RESULT.tracklist.back().extraartists.back().name = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	case StateKey::master_tracklist_extraartists_anv:
		RESULT.tracklist.back().extraartists.back().anv = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	case StateKey::master_tracklist_extraartists_tracks:
		RESULT.tracklist.back().extraartists.back().tracks = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	case StateKey::master_tracklist_extraartists_role:
		RESULT.tracklist.back().extraartists.back().role = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	case StateKey::master_tracklist_extraartists_resource_url:
		RESULT.tracklist.back().extraartists.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::master_tracklist_extraartists;
		break;
	default:
		return false;
	}
	return true;
}
bool master_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::master_videos_embed:
		RESULT.videos.back().embed = value;
		m_state = StateKey::master_videos;
		break;
	default:
		return false;
	}
	return true;
}
bool master_parser::Double(double value)
{
	switch(m_state){
	case StateKey::master_lowest_price:
		RESULT.lowest_price = value;
		m_state = StateKey::master;
		break;
	default:
		return false;
	}
	return true;
}
bool master_parser::Number(int value)
{
	switch(m_state){
	case StateKey::master_id:
		RESULT.id = value;
		m_state = StateKey::master;
		break;
	case StateKey::master_year:
		RESULT.year = value;
		m_state = StateKey::master;
		break;
	case StateKey::master_num_for_sale:
		RESULT.num_for_sale = value;
		m_state = StateKey::master;
		break;
	case StateKey::master_main_release:
		RESULT.main_release = value;
		m_state = StateKey::master;
		break;
	case StateKey::master_images_height:
		RESULT.images.back().height = value;
		m_state = StateKey::master_images;
		break;
	case StateKey::master_images_width:
		RESULT.images.back().width = value;
		m_state = StateKey::master_images;
		break;
	case StateKey::master_videos_duration:
		RESULT.videos.back().duration = value;
		m_state = StateKey::master_videos;
		break;
	case StateKey::master_artists_id:
		RESULT.artists.back().id = value;
		m_state = StateKey::master_artists;
		break;
	case StateKey::master_tracklist_artists_id:
		RESULT.tracklist.back().artists.back().id = value;
		m_state = StateKey::master_tracklist_artists;
		break;
	case StateKey::master_tracklist_extraartists_id:
		RESULT.tracklist.back().extraartists.back().id = value;
		m_state = StateKey::master_tracklist_extraartists;
		break;
	default:
		return false;
	}
	return true;
}
bool master_parser::RawNumber(const Ch*, rapidjson::SizeType, bool)
{
	return false;
}

bool master_parser::Null()
{
	switch(m_state){
		case StateKey::master_id:
			m_state = StateKey::master;
			break;
		case StateKey::master_year:
			m_state = StateKey::master;
			break;
		case StateKey::master_num_for_sale:
			m_state = StateKey::master;
			break;
		case StateKey::master_main_release:
			m_state = StateKey::master;
			break;
		case StateKey::master_lowest_price:
			m_state = StateKey::master;
			break;
		case StateKey::master_uri:
			m_state = StateKey::master;
			break;
		case StateKey::master_title:
			m_state = StateKey::master;
			break;
		case StateKey::master_versions_url:
			m_state = StateKey::master;
			break;
		case StateKey::master_resource_url:
			m_state = StateKey::master;
			break;
		case StateKey::master_data_quality:
			m_state = StateKey::master;
			break;
		case StateKey::master_main_release_url:
			m_state = StateKey::master;
			break;
		case StateKey::master_styles:
			m_state = StateKey::master;
			break;
		case StateKey::master_genres:
			m_state = StateKey::master;
			break;
		case StateKey::master_images:
			m_state = StateKey::master;
			break;
		case StateKey::master_images_height:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_images_width:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_images_uri:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_images_resource_url:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_images_type:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_images_uri150:
			m_state = StateKey::master_images;
			break;
		case StateKey::master_videos:
			m_state = StateKey::master;
			break;
		case StateKey::master_videos_duration:
			m_state = StateKey::master_videos;
			break;
		case StateKey::master_videos_embed:
			m_state = StateKey::master_videos;
			break;
		case StateKey::master_videos_description:
			m_state = StateKey::master_videos;
			break;
		case StateKey::master_videos_title:
			m_state = StateKey::master_videos;
			break;
		case StateKey::master_videos_uri:
			m_state = StateKey::master_videos;
			break;
		case StateKey::master_artists:
			m_state = StateKey::master;
			break;
		case StateKey::master_artists_id:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_join:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_name:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_anv:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_tracks:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_role:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_artists_resource_url:
			m_state = StateKey::master_artists;
			break;
		case StateKey::master_tracklist:
			m_state = StateKey::master;
			break;
		case StateKey::master_tracklist_duration:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_position:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_type_:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_title:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_artists:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_artists_id:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_join:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_name:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_anv:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_tracks:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_role:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_artists_resource_url:
			m_state = StateKey::master_tracklist_artists;
			break;
		case StateKey::master_tracklist_extraartists:
			m_state = StateKey::master_tracklist;
			break;
		case StateKey::master_tracklist_extraartists_id:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_join:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_name:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_anv:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_tracks:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_role:
			m_state = StateKey::master_tracklist_extraartists;
			break;
		case StateKey::master_tracklist_extraartists_resource_url:
			m_state = StateKey::master_tracklist_extraartists;
			break;
	}
	return true;
}
bool master_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::master_images:
		if(length == 6 && platform::strcmp(str, STR("height")) == 0){
			m_state = StateKey::master_images_height;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("width")) == 0){
			m_state = StateKey::master_images_width;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::master_images_uri;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::master_images_resource_url;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::master_images_type;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("uri150")) == 0){
			m_state = StateKey::master_images_uri150;
		}
		else {
			return false;
		}
		break;
	case StateKey::master_videos:
		if(length == 8 && platform::strcmp(str, STR("duration")) == 0){
			m_state = StateKey::master_videos_duration;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("embed")) == 0){
			m_state = StateKey::master_videos_embed;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("description")) == 0){
			m_state = StateKey::master_videos_description;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::master_videos_title;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::master_videos_uri;
		}
		else {
			return false;
		}
		break;
	case StateKey::master_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::master_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::master_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::master_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::master_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::master_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::master_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::master_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::master_tracklist_artists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::master_tracklist_artists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::master_tracklist_artists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::master_tracklist_artists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::master_tracklist_artists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::master_tracklist_artists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::master_tracklist_artists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::master_tracklist_artists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::master_tracklist_extraartists:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::master_tracklist_extraartists_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("join")) == 0){
			m_state = StateKey::master_tracklist_extraartists_join;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("name")) == 0){
			m_state = StateKey::master_tracklist_extraartists_name;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("anv")) == 0){
			m_state = StateKey::master_tracklist_extraartists_anv;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("tracks")) == 0){
			m_state = StateKey::master_tracklist_extraartists_tracks;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("role")) == 0){
			m_state = StateKey::master_tracklist_extraartists_role;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::master_tracklist_extraartists_resource_url;
		}
		else {
			return false;
		}
		break;
	case StateKey::master_tracklist:
		if(length == 8 && platform::strcmp(str, STR("duration")) == 0){
			m_state = StateKey::master_tracklist_duration;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("position")) == 0){
			m_state = StateKey::master_tracklist_position;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("type_")) == 0){
			m_state = StateKey::master_tracklist_type_;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::master_tracklist_title;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::master_tracklist_artists;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("extraartists")) == 0){
			m_state = StateKey::master_tracklist_extraartists;
		}
		else {
			return false;
		}
		break;
	case StateKey::master:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::master_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::master_year;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("num_for_sale")) == 0){
			m_state = StateKey::master_num_for_sale;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("main_release")) == 0){
			m_state = StateKey::master_main_release;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("lowest_price")) == 0){
			m_state = StateKey::master_lowest_price;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::master_uri;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::master_title;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("versions_url")) == 0){
			m_state = StateKey::master_versions_url;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::master_resource_url;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("data_quality")) == 0){
			m_state = StateKey::master_data_quality;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("main_release_url")) == 0){
			m_state = StateKey::master_main_release_url;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("styles")) == 0){
			m_state = StateKey::master_styles;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("genres")) == 0){
			m_state = StateKey::master_genres;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("images")) == 0){
			m_state = StateKey::master_images;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("videos")) == 0){
			m_state = StateKey::master_videos;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("artists")) == 0){
			m_state = StateKey::master_artists;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("tracklist")) == 0){
			m_state = StateKey::master_tracklist;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool master_parser::StartArray()
{
	return true;
}
bool master_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::master_styles:
		m_state = StateKey::master;
		break;
	case StateKey::master_genres:
		m_state = StateKey::master;
		break;
	case StateKey::master_images:
		m_state = StateKey::master;
		break;
	case StateKey::master_videos:
		m_state = StateKey::master;
		break;
	case StateKey::master_artists:
		m_state = StateKey::master;
		break;
	case StateKey::master_tracklist:
		m_state = StateKey::master;
		break;
	case StateKey::master_tracklist_artists:
		m_state = StateKey::master_tracklist;
		break;
	case StateKey::master_tracklist_extraartists:
		m_state = StateKey::master_tracklist;
		break;
	}
	return true;
}

bool master_parser::StartObject()
{
	switch(m_state){
	case StateKey::master_images:
		RESULT.images.emplace_back();
		break;
	case StateKey::master_videos:
		RESULT.videos.emplace_back();
		break;
	case StateKey::master_artists:
		RESULT.artists.emplace_back();
		break;
	case StateKey::master_tracklist:
		RESULT.tracklist.emplace_back();
		break;
	case StateKey::master_tracklist_artists:
		RESULT.tracklist.back().artists.emplace_back();
		break;
	case StateKey::master_tracklist_extraartists:
		RESULT.tracklist.back().extraartists.emplace_back();
		break;
	}
	return true;
}

bool master_parser::EndObject(rapidjson::SizeType memberCount)
{
	return true;
}

master_parser::master_parser()
{
	m_state = StateKey::master;
}

} // namespace discogs
} // namespace result
