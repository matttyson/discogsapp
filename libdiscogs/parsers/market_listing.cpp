/* clang-format off */
#include "market_listing_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	listing,
	listing_in_cart,
	listing_allow_offers,
	listing_audio,
	listing_id,
	listing_status,
	listing_ships_from,
	listing_uri,
	listing_comments,
	listing_sleeve_condition,
	listing_resource_url,
	listing_condition,
	listing_posted,
	listing_original_shipping_price,
	listing_original_shipping_price_curr_id,
	listing_original_shipping_price_curr_abbr,
	listing_original_shipping_price_formatted,
	listing_original_shipping_price_value,
	listing_original_shipping_price_converted,
	listing_original_shipping_price_converted_curr_id,
	listing_original_shipping_price_converted_curr_abbr,
	listing_original_shipping_price_converted_formatted,
	listing_original_shipping_price_converted_value,
	listing_price,
	listing_price_value,
	listing_price_currency,
	listing_shipping_price,
	listing_shipping_price_currency,
	listing_shipping_price_value,
	listing_seller,
	listing_seller_id,
	listing_seller_uid,
	listing_seller_username,
	listing_seller_url,
	listing_seller_html_url,
	listing_seller_shipping,
	listing_seller_payment,
	listing_seller_avatar_url,
	listing_seller_resource_url,
	listing_seller_stats,
	listing_seller_stats_total,
	listing_seller_stats_rating,
	listing_seller_stats_stars,
	listing_release,
	listing_release_id,
	listing_release_year,
	listing_release_description,
	listing_release_format,
	listing_release_catalog_number,
	listing_release_artist,
	listing_release_title,
	listing_release_resource_url,
	listing_release_thumbnail,
	listing_release_images,
	listing_release_images_height,
	listing_release_images_width,
	listing_release_images_uri,
	listing_release_images_resource_url,
	listing_release_images_type,
	listing_release_images_uri150,
	listing_release_stats,
	listing_release_stats_user,
	listing_release_stats_user_in_collection,
	listing_release_stats_user_in_wantlist,
	listing_release_stats_community,
	listing_release_stats_community_in_collection,
	listing_release_stats_community_in_wantlist,
	listing_original_price,
	listing_original_price_curr_id,
	listing_original_price_curr_abbr,
	listing_original_price_formatted,
	listing_original_price_value,
	listing_original_price_converted,
	listing_original_price_converted_curr_id,
	listing_original_price_converted_curr_abbr,
	listing_original_price_converted_formatted,
	listing_original_price_converted_value,
};

bool market_listing_parser::Int(int value)
{
	return Number((int)value);
}

bool market_listing_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool market_listing_parser::Int64(int64_t i)
{
	return false;
}

bool market_listing_parser::Uint64(uint64_t i)
{
	return false;
}
bool market_listing_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::listing_status:
		RESULT.status = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_ships_from:
		RESULT.ships_from = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_uri:
		RESULT.uri = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_comments:
		RESULT.comments = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_sleeve_condition:
		RESULT.sleeve_condition = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_resource_url:
		RESULT.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_condition:
		RESULT.condition = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_posted:
		RESULT.posted = ::platform::string_t(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_original_shipping_price_curr_abbr:
		RESULT.original_shipping_price_.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price;
		break;
	case StateKey::listing_original_shipping_price_formatted:
		RESULT.original_shipping_price_.formatted = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price;
		break;
	case StateKey::listing_original_shipping_price_converted_curr_abbr:
		RESULT.original_shipping_price_.converted.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price_converted;
		break;
	case StateKey::listing_original_shipping_price_converted_formatted:
		RESULT.original_shipping_price_.converted.formatted = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price_converted;
		break;
	case StateKey::listing_price_currency:
		RESULT.price_.currency = ::platform::string_t(value, length);
		m_state = StateKey::listing_price;
		break;
	case StateKey::listing_shipping_price_currency:
		RESULT.shipping_price_.currency = ::platform::string_t(value, length);
		m_state = StateKey::listing_shipping_price;
		break;
	case StateKey::listing_seller_username:
		RESULT.seller_.username = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_url:
		RESULT.seller_.url = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_html_url:
		RESULT.seller_.html_url = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_shipping:
		RESULT.seller_.shipping = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_payment:
		RESULT.seller_.payment = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_avatar_url:
		RESULT.seller_.avatar_url = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_resource_url:
		RESULT.seller_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_stats_rating:
		RESULT.seller_.stats_.rating = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller_stats;
		break;
	case StateKey::listing_release_description:
		RESULT.release.description = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_format:
		RESULT.release.format = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_catalog_number:
		RESULT.release.catalog_number = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_artist:
		RESULT.release.artist = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_title:
		RESULT.release.title = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_resource_url:
		RESULT.release.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_thumbnail:
		RESULT.release.thumbnail = ::platform::string_t(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_images_uri:
		RESULT.release.images.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_release_images_resource_url:
		RESULT.release.images.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_release_images_type:
		RESULT.release.images.back().type = ::platform::string_t(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_release_images_uri150:
		RESULT.release.images.back().uri150 = ::platform::string_t(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_original_price_curr_abbr:
		RESULT.original_price_.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price;
		break;
	case StateKey::listing_original_price_formatted:
		RESULT.original_price_.formatted = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price;
		break;
	case StateKey::listing_original_price_converted_curr_abbr:
		RESULT.original_price_.converted.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price_converted;
		break;
	case StateKey::listing_original_price_converted_formatted:
		RESULT.original_price_.converted.formatted = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price_converted;
		break;
	default:
		return false;
	}
	return true;
}
bool market_listing_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::listing_in_cart:
		RESULT.in_cart = value;
		m_state = StateKey::listing;
		break;
	case StateKey::listing_allow_offers:
		RESULT.allow_offers = value;
		m_state = StateKey::listing;
		break;
	case StateKey::listing_audio:
		RESULT.audio = value;
		m_state = StateKey::listing;
		break;
	default:
		return false;
	}
	return true;
}
bool market_listing_parser::RawNumber(const Ch * value, rapidjson::SizeType length, bool)
{
	switch(m_state){
	case StateKey::listing_id:
		RESULT.id = str_to_int(value, length);
		m_state = StateKey::listing;
		break;
	case StateKey::listing_original_shipping_price_curr_id:
		RESULT.original_shipping_price_.curr_id = str_to_int(value, length);
		m_state = StateKey::listing_original_shipping_price;
		break;
	case StateKey::listing_original_shipping_price_value:
		RESULT.original_shipping_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price;
		break;
	case StateKey::listing_original_shipping_price_converted_curr_id:
		RESULT.original_shipping_price_.converted.curr_id = str_to_int(value, length);
		m_state = StateKey::listing_original_shipping_price_converted;
		break;
	case StateKey::listing_original_shipping_price_converted_value:
		RESULT.original_shipping_price_.converted.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_shipping_price_converted;
		break;
	case StateKey::listing_price_value:
		RESULT.price_.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_price;
		break;
	case StateKey::listing_shipping_price_value:
		RESULT.shipping_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_shipping_price;
		break;
	case StateKey::listing_seller_id:
		RESULT.seller_.id = str_to_int(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_uid:
		RESULT.seller_.uid = str_to_int(value, length);
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_seller_stats_total:
		RESULT.seller_.stats_.total = str_to_int(value, length);
		m_state = StateKey::listing_seller_stats;
		break;
	case StateKey::listing_seller_stats_stars:
		RESULT.seller_.stats_.stars = ::platform::string_t(value, length);
		m_state = StateKey::listing_seller_stats;
		break;
	case StateKey::listing_release_id:
		RESULT.release.id = str_to_int(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_year:
		RESULT.release.year = str_to_int(value, length);
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_images_height:
		RESULT.release.images.back().height = str_to_int(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_release_images_width:
		RESULT.release.images.back().width = str_to_int(value, length);
		m_state = StateKey::listing_release_images;
		break;
	case StateKey::listing_release_stats_user_in_collection:
		RESULT.release.stats.user.in_collection = str_to_int(value, length);
		m_state = StateKey::listing_release_stats_user;
		break;
	case StateKey::listing_release_stats_user_in_wantlist:
		RESULT.release.stats.user.in_wantlist = str_to_int(value, length);
		m_state = StateKey::listing_release_stats_user;
		break;
	case StateKey::listing_release_stats_community_in_collection:
		RESULT.release.stats.community.in_collection = str_to_int(value, length);
		m_state = StateKey::listing_release_stats_community;
		break;
	case StateKey::listing_release_stats_community_in_wantlist:
		RESULT.release.stats.community.in_wantlist = str_to_int(value, length);
		m_state = StateKey::listing_release_stats_community;
		break;
	case StateKey::listing_original_price_curr_id:
		RESULT.original_price_.curr_id = str_to_int(value, length);
		m_state = StateKey::listing_original_price;
		break;
	case StateKey::listing_original_price_value:
		RESULT.original_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price;
		break;
	case StateKey::listing_original_price_converted_curr_id:
		RESULT.original_price_.converted.curr_id = str_to_int(value, length);
		m_state = StateKey::listing_original_price_converted;
		break;
	case StateKey::listing_original_price_converted_value:
		RESULT.original_price_.converted.value = ::platform::string_t(value, length);
		m_state = StateKey::listing_original_price_converted;
		break;
	default:
		return false;
	}
	return true;
}

bool market_listing_parser::Number(int)
{
	return false;
}

bool market_listing_parser::Double(double)
{
	return false;
}

bool market_listing_parser::Null()
{
	switch(m_state){
		case StateKey::listing_in_cart:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_allow_offers:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_audio:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_id:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_status:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_ships_from:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_uri:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_comments:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_sleeve_condition:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_resource_url:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_condition:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_posted:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_original_shipping_price:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_original_shipping_price_curr_id:
			m_state = StateKey::listing_original_shipping_price;
			break;
		case StateKey::listing_original_shipping_price_curr_abbr:
			m_state = StateKey::listing_original_shipping_price;
			break;
		case StateKey::listing_original_shipping_price_formatted:
			m_state = StateKey::listing_original_shipping_price;
			break;
		case StateKey::listing_original_shipping_price_value:
			m_state = StateKey::listing_original_shipping_price;
			break;
		case StateKey::listing_original_shipping_price_converted:
			m_state = StateKey::listing_original_shipping_price;
			break;
		case StateKey::listing_original_shipping_price_converted_curr_id:
			m_state = StateKey::listing_original_shipping_price_converted;
			break;
		case StateKey::listing_original_shipping_price_converted_curr_abbr:
			m_state = StateKey::listing_original_shipping_price_converted;
			break;
		case StateKey::listing_original_shipping_price_converted_formatted:
			m_state = StateKey::listing_original_shipping_price_converted;
			break;
		case StateKey::listing_original_shipping_price_converted_value:
			m_state = StateKey::listing_original_shipping_price_converted;
			break;
		case StateKey::listing_price:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_price_value:
			m_state = StateKey::listing_price;
			break;
		case StateKey::listing_price_currency:
			m_state = StateKey::listing_price;
			break;
		case StateKey::listing_shipping_price:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_shipping_price_currency:
			m_state = StateKey::listing_shipping_price;
			break;
		case StateKey::listing_shipping_price_value:
			m_state = StateKey::listing_shipping_price;
			break;
		case StateKey::listing_seller:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_seller_id:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_uid:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_username:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_url:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_html_url:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_shipping:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_payment:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_avatar_url:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_resource_url:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_stats:
			m_state = StateKey::listing_seller;
			break;
		case StateKey::listing_seller_stats_total:
			m_state = StateKey::listing_seller_stats;
			break;
		case StateKey::listing_seller_stats_rating:
			m_state = StateKey::listing_seller_stats;
			break;
		case StateKey::listing_seller_stats_stars:
			m_state = StateKey::listing_seller_stats;
			break;
		case StateKey::listing_release:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_release_id:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_year:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_description:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_format:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_catalog_number:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_artist:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_title:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_resource_url:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_thumbnail:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_images:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_images_height:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_images_width:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_images_uri:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_images_resource_url:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_images_type:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_images_uri150:
			m_state = StateKey::listing_release_images;
			break;
		case StateKey::listing_release_stats:
			m_state = StateKey::listing_release;
			break;
		case StateKey::listing_release_stats_user:
			m_state = StateKey::listing_release_stats;
			break;
		case StateKey::listing_release_stats_user_in_collection:
			m_state = StateKey::listing_release_stats_user;
			break;
		case StateKey::listing_release_stats_user_in_wantlist:
			m_state = StateKey::listing_release_stats_user;
			break;
		case StateKey::listing_release_stats_community:
			m_state = StateKey::listing_release_stats;
			break;
		case StateKey::listing_release_stats_community_in_collection:
			m_state = StateKey::listing_release_stats_community;
			break;
		case StateKey::listing_release_stats_community_in_wantlist:
			m_state = StateKey::listing_release_stats_community;
			break;
		case StateKey::listing_original_price:
			m_state = StateKey::listing;
			break;
		case StateKey::listing_original_price_curr_id:
			m_state = StateKey::listing_original_price;
			break;
		case StateKey::listing_original_price_curr_abbr:
			m_state = StateKey::listing_original_price;
			break;
		case StateKey::listing_original_price_formatted:
			m_state = StateKey::listing_original_price;
			break;
		case StateKey::listing_original_price_value:
			m_state = StateKey::listing_original_price;
			break;
		case StateKey::listing_original_price_converted:
			m_state = StateKey::listing_original_price;
			break;
		case StateKey::listing_original_price_converted_curr_id:
			m_state = StateKey::listing_original_price_converted;
			break;
		case StateKey::listing_original_price_converted_curr_abbr:
			m_state = StateKey::listing_original_price_converted;
			break;
		case StateKey::listing_original_price_converted_formatted:
			m_state = StateKey::listing_original_price_converted;
			break;
		case StateKey::listing_original_price_converted_value:
			m_state = StateKey::listing_original_price_converted;
			break;
	}
	return true;
}
bool market_listing_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::listing_original_shipping_price_converted:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::listing_original_shipping_price_converted_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::listing_original_shipping_price_converted_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::listing_original_shipping_price_converted_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_original_shipping_price_converted_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_original_shipping_price:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::listing_original_shipping_price_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::listing_original_shipping_price_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::listing_original_shipping_price_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_original_shipping_price_value;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("converted")) == 0){
			m_state = StateKey::listing_original_shipping_price_converted;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_price:
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_price_value;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("currency")) == 0){
			m_state = StateKey::listing_price_currency;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_shipping_price:
		if(length == 8 && platform::strcmp(str, STR("currency")) == 0){
			m_state = StateKey::listing_shipping_price_currency;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_shipping_price_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_seller_stats:
		if(length == 5 && platform::strcmp(str, STR("total")) == 0){
			m_state = StateKey::listing_seller_stats_total;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::listing_seller_stats_rating;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stars")) == 0){
			m_state = StateKey::listing_seller_stats_stars;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_seller:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::listing_seller_id;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uid")) == 0){
			m_state = StateKey::listing_seller_uid;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("username")) == 0){
			m_state = StateKey::listing_seller_username;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("url")) == 0){
			m_state = StateKey::listing_seller_url;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("html_url")) == 0){
			m_state = StateKey::listing_seller_html_url;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("shipping")) == 0){
			m_state = StateKey::listing_seller_shipping;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("payment")) == 0){
			m_state = StateKey::listing_seller_payment;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("avatar_url")) == 0){
			m_state = StateKey::listing_seller_avatar_url;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::listing_seller_resource_url;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stats")) == 0){
			m_state = StateKey::listing_seller_stats;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_release_images:
		if(length == 6 && platform::strcmp(str, STR("height")) == 0){
			m_state = StateKey::listing_release_images_height;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("width")) == 0){
			m_state = StateKey::listing_release_images_width;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::listing_release_images_uri;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::listing_release_images_resource_url;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::listing_release_images_type;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("uri150")) == 0){
			m_state = StateKey::listing_release_images_uri150;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_release_stats_user:
		if(length == 13 && platform::strcmp(str, STR("in_collection")) == 0){
			m_state = StateKey::listing_release_stats_user_in_collection;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("in_wantlist")) == 0){
			m_state = StateKey::listing_release_stats_user_in_wantlist;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_release_stats_community:
		if(length == 13 && platform::strcmp(str, STR("in_collection")) == 0){
			m_state = StateKey::listing_release_stats_community_in_collection;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("in_wantlist")) == 0){
			m_state = StateKey::listing_release_stats_community_in_wantlist;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_release_stats:
		if(length == 4 && platform::strcmp(str, STR("user")) == 0){
			m_state = StateKey::listing_release_stats_user;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("community")) == 0){
			m_state = StateKey::listing_release_stats_community;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_release:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::listing_release_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::listing_release_year;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("description")) == 0){
			m_state = StateKey::listing_release_description;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("format")) == 0){
			m_state = StateKey::listing_release_format;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("catalog_number")) == 0){
			m_state = StateKey::listing_release_catalog_number;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("artist")) == 0){
			m_state = StateKey::listing_release_artist;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::listing_release_title;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::listing_release_resource_url;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("thumbnail")) == 0){
			m_state = StateKey::listing_release_thumbnail;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("images")) == 0){
			m_state = StateKey::listing_release_images;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stats")) == 0){
			m_state = StateKey::listing_release_stats;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_original_price_converted:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::listing_original_price_converted_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::listing_original_price_converted_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::listing_original_price_converted_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_original_price_converted_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing_original_price:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::listing_original_price_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::listing_original_price_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::listing_original_price_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::listing_original_price_value;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("converted")) == 0){
			m_state = StateKey::listing_original_price_converted;
		}
		else {
			return false;
		}
		break;
	case StateKey::listing:
		if(length == 7 && platform::strcmp(str, STR("in_cart")) == 0){
			m_state = StateKey::listing_in_cart;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("allow_offers")) == 0){
			m_state = StateKey::listing_allow_offers;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("audio")) == 0){
			m_state = StateKey::listing_audio;
		}
		else
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::listing_id;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("status")) == 0){
			m_state = StateKey::listing_status;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("ships_from")) == 0){
			m_state = StateKey::listing_ships_from;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::listing_uri;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("comments")) == 0){
			m_state = StateKey::listing_comments;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("sleeve_condition")) == 0){
			m_state = StateKey::listing_sleeve_condition;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::listing_resource_url;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("condition")) == 0){
			m_state = StateKey::listing_condition;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("posted")) == 0){
			m_state = StateKey::listing_posted;
		}
		else
		if(length == 23 && platform::strcmp(str, STR("original_shipping_price")) == 0){
			m_state = StateKey::listing_original_shipping_price;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("price")) == 0){
			m_state = StateKey::listing_price;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("shipping_price")) == 0){
			m_state = StateKey::listing_shipping_price;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("seller")) == 0){
			m_state = StateKey::listing_seller;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("release")) == 0){
			m_state = StateKey::listing_release;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("original_price")) == 0){
			m_state = StateKey::listing_original_price;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool market_listing_parser::StartArray()
{
	return true;
}
bool market_listing_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::listing_release_images:
		m_state = StateKey::listing_release;
		break;
	}
	return true;
}

bool market_listing_parser::StartObject()
{
	switch(m_state){
	case StateKey::listing_release_images:
		RESULT.release.images.emplace_back();
		break;
	}
	return true;
}

bool market_listing_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::listing_original_shipping_price:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_original_shipping_price_converted:
		m_state = StateKey::listing_original_shipping_price;
		break;
	case StateKey::listing_price:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_shipping_price:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_seller:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_seller_stats:
		m_state = StateKey::listing_seller;
		break;
	case StateKey::listing_release:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_release_stats:
		m_state = StateKey::listing_release;
		break;
	case StateKey::listing_release_stats_user:
		m_state = StateKey::listing_release_stats;
		break;
	case StateKey::listing_release_stats_community:
		m_state = StateKey::listing_release_stats;
		break;
	case StateKey::listing_original_price:
		m_state = StateKey::listing;
		break;
	case StateKey::listing_original_price_converted:
		m_state = StateKey::listing_original_price;
		break;
	}
	return true;
}

market_listing_parser::market_listing_parser()
{
	m_state = StateKey::listing;
}

} // namespace discogs
} // namespace parser
