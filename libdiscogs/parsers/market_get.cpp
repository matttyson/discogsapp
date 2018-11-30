/* clang-format off */
#include "market_get_parser.hpp"
#include "libplatform/platform.hpp"
namespace discogs {
namespace parser {

enum class StateKey {
	market_listing,
	market_listing_listings,
	market_listing_listings_in_cart,
	market_listing_listings_allow_offers,
	market_listing_listings_audio,
	market_listing_listings_id,
	market_listing_listings_status,
	market_listing_listings_ships_from,
	market_listing_listings_uri,
	market_listing_listings_comments,
	market_listing_listings_sleeve_condition,
	market_listing_listings_resource_url,
	market_listing_listings_condition,
	market_listing_listings_posted,
	market_listing_listings_original_shipping_price,
	market_listing_listings_original_shipping_price_curr_id,
	market_listing_listings_original_shipping_price_curr_abbr,
	market_listing_listings_original_shipping_price_formatted,
	market_listing_listings_original_shipping_price_value,
	market_listing_listings_original_shipping_price_converted,
	market_listing_listings_original_shipping_price_converted_curr_id,
	market_listing_listings_original_shipping_price_converted_curr_abbr,
	market_listing_listings_original_shipping_price_converted_formatted,
	market_listing_listings_original_shipping_price_converted_value,
	market_listing_listings_price,
	market_listing_listings_price_value,
	market_listing_listings_price_currency,
	market_listing_listings_shipping_price,
	market_listing_listings_shipping_price_currency,
	market_listing_listings_shipping_price_value,
	market_listing_listings_seller,
	market_listing_listings_seller_id,
	market_listing_listings_seller_uid,
	market_listing_listings_seller_username,
	market_listing_listings_seller_url,
	market_listing_listings_seller_html_url,
	market_listing_listings_seller_shipping,
	market_listing_listings_seller_payment,
	market_listing_listings_seller_avatar_url,
	market_listing_listings_seller_resource_url,
	market_listing_listings_seller_stats,
	market_listing_listings_seller_stats_total,
	market_listing_listings_seller_stats_rating,
	market_listing_listings_seller_stats_stars,
	market_listing_listings_release,
	market_listing_listings_release_id,
	market_listing_listings_release_year,
	market_listing_listings_release_description,
	market_listing_listings_release_format,
	market_listing_listings_release_catalog_number,
	market_listing_listings_release_artist,
	market_listing_listings_release_title,
	market_listing_listings_release_resource_url,
	market_listing_listings_release_thumbnail,
	market_listing_listings_release_images,
	market_listing_listings_release_images_height,
	market_listing_listings_release_images_width,
	market_listing_listings_release_images_uri,
	market_listing_listings_release_images_resource_url,
	market_listing_listings_release_images_type,
	market_listing_listings_release_images_uri150,
	market_listing_listings_release_stats,
	market_listing_listings_release_stats_user,
	market_listing_listings_release_stats_user_in_collection,
	market_listing_listings_release_stats_user_in_wantlist,
	market_listing_listings_release_stats_community,
	market_listing_listings_release_stats_community_in_collection,
	market_listing_listings_release_stats_community_in_wantlist,
	market_listing_listings_original_price,
	market_listing_listings_original_price_curr_id,
	market_listing_listings_original_price_curr_abbr,
	market_listing_listings_original_price_formatted,
	market_listing_listings_original_price_value,
	market_listing_listings_original_price_converted,
	market_listing_listings_original_price_converted_curr_id,
	market_listing_listings_original_price_converted_curr_abbr,
	market_listing_listings_original_price_converted_formatted,
	market_listing_listings_original_price_converted_value,
	market_listing_pagination,
	market_listing_pagination_per_page,
	market_listing_pagination_items,
	market_listing_pagination_page,
	market_listing_pagination_pages,
	market_listing_pagination_urls,
	market_listing_pagination_urls_next,
	market_listing_pagination_urls_last,
	market_listing_pagination_urls_first,
	market_listing_pagination_urls_prev,
};

bool market_get_parser::Int(int value)
{
	return Number((int)value);
}

bool market_get_parser::Uint(unsigned int value)
{
	return Number((int)value);
}

bool market_get_parser::Int64(int64_t i)
{
	return false;
}

bool market_get_parser::Uint64(uint64_t i)
{
	return false;
}
bool market_get_parser::String(const Ch* value, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::market_listing_listings_status:
		RESULT.listings.back().status = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_ships_from:
		RESULT.listings.back().ships_from = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_uri:
		RESULT.listings.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_comments:
		RESULT.listings.back().comments = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_sleeve_condition:
		RESULT.listings.back().sleeve_condition = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_resource_url:
		RESULT.listings.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_condition:
		RESULT.listings.back().condition = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_posted:
		RESULT.listings.back().posted = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_original_shipping_price_curr_abbr:
		RESULT.listings.back().original_shipping_price_.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price;
		break;
	case StateKey::market_listing_listings_original_shipping_price_formatted:
		RESULT.listings.back().original_shipping_price_.formatted = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price;
		break;
	case StateKey::market_listing_listings_original_shipping_price_converted_curr_abbr:
		RESULT.listings.back().original_shipping_price_.converted.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price_converted;
		break;
	case StateKey::market_listing_listings_original_shipping_price_converted_formatted:
		RESULT.listings.back().original_shipping_price_.converted.formatted = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price_converted;
		break;
	case StateKey::market_listing_listings_price_currency:
		RESULT.listings.back().price_.currency = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_price;
		break;
	case StateKey::market_listing_listings_shipping_price_currency:
		RESULT.listings.back().shipping_price_.currency = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_shipping_price;
		break;
	case StateKey::market_listing_listings_seller_username:
		RESULT.listings.back().seller_.username = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_url:
		RESULT.listings.back().seller_.url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_html_url:
		RESULT.listings.back().seller_.html_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_shipping:
		RESULT.listings.back().seller_.shipping = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_payment:
		RESULT.listings.back().seller_.payment = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_avatar_url:
		RESULT.listings.back().seller_.avatar_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_resource_url:
		RESULT.listings.back().seller_.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_stats_rating:
		RESULT.listings.back().seller_.stats_.rating = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller_stats;
		break;
	case StateKey::market_listing_listings_release_description:
		RESULT.listings.back().release.description = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_format:
		RESULT.listings.back().release.format = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_catalog_number:
		RESULT.listings.back().release.catalog_number = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_artist:
		RESULT.listings.back().release.artist = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_title:
		RESULT.listings.back().release.title = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_resource_url:
		RESULT.listings.back().release.resource_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_thumbnail:
		RESULT.listings.back().release.thumbnail = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_images_uri:
		RESULT.listings.back().release.images.back().uri = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_release_images_resource_url:
		RESULT.listings.back().release.images.back().resource_url = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_release_images_type:
		RESULT.listings.back().release.images.back().type = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_release_images_uri150:
		RESULT.listings.back().release.images.back().uri150 = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_original_price_curr_abbr:
		RESULT.listings.back().original_price_.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price;
		break;
	case StateKey::market_listing_listings_original_price_formatted:
		RESULT.listings.back().original_price_.formatted = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price;
		break;
	case StateKey::market_listing_listings_original_price_converted_curr_abbr:
		RESULT.listings.back().original_price_.converted.curr_abbr = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price_converted;
		break;
	case StateKey::market_listing_listings_original_price_converted_formatted:
		RESULT.listings.back().original_price_.converted.formatted = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price_converted;
		break;
	case StateKey::market_listing_pagination_urls_next:
		RESULT.pages.links.next = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_pagination_urls;
		break;
	case StateKey::market_listing_pagination_urls_last:
		RESULT.pages.links.last = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_pagination_urls;
		break;
	case StateKey::market_listing_pagination_urls_first:
		RESULT.pages.links.first = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_pagination_urls;
		break;
	case StateKey::market_listing_pagination_urls_prev:
		RESULT.pages.links.prev = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_pagination_urls;
		break;
	default:
		return false;
	}
	return true;
}
bool market_get_parser::Bool(bool value)
{
	switch(m_state){
	case StateKey::market_listing_listings_in_cart:
		RESULT.listings.back().in_cart = value;
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_allow_offers:
		RESULT.listings.back().allow_offers = value;
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_audio:
		RESULT.listings.back().audio = value;
		m_state = StateKey::market_listing_listings;
		break;
	default:
		return false;
	}
	return true;
}
bool market_get_parser::RawNumber(const Ch * value, rapidjson::SizeType length, bool)
{
	switch(m_state){
	case StateKey::market_listing_listings_id:
		RESULT.listings.back().id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_original_shipping_price_curr_id:
		RESULT.listings.back().original_shipping_price_.curr_id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price;
		break;
	case StateKey::market_listing_listings_original_shipping_price_value:
		RESULT.listings.back().original_shipping_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price;
		break;
	case StateKey::market_listing_listings_original_shipping_price_converted_curr_id:
		RESULT.listings.back().original_shipping_price_.converted.curr_id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price_converted;
		break;
	case StateKey::market_listing_listings_original_shipping_price_converted_value:
		RESULT.listings.back().original_shipping_price_.converted.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_shipping_price_converted;
		break;
	case StateKey::market_listing_listings_price_value:
		RESULT.listings.back().price_.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_price;
		break;
	case StateKey::market_listing_listings_shipping_price_value:
		RESULT.listings.back().shipping_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_shipping_price;
		break;
	case StateKey::market_listing_listings_seller_id:
		RESULT.listings.back().seller_.id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_uid:
		RESULT.listings.back().seller_.uid = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_seller_stats_total:
		RESULT.listings.back().seller_.stats_.total = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_seller_stats;
		break;
	case StateKey::market_listing_listings_seller_stats_stars:
		RESULT.listings.back().seller_.stats_.stars = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_seller_stats;
		break;
	case StateKey::market_listing_listings_release_id:
		RESULT.listings.back().release.id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_year:
		RESULT.listings.back().release.year = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_images_height:
		RESULT.listings.back().release.images.back().height = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_release_images_width:
		RESULT.listings.back().release.images.back().width = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_images;
		break;
	case StateKey::market_listing_listings_release_stats_user_in_collection:
		RESULT.listings.back().release.stats.user.in_collection = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_stats_user;
		break;
	case StateKey::market_listing_listings_release_stats_user_in_wantlist:
		RESULT.listings.back().release.stats.user.in_wantlist = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_stats_user;
		break;
	case StateKey::market_listing_listings_release_stats_community_in_collection:
		RESULT.listings.back().release.stats.community.in_collection = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_stats_community;
		break;
	case StateKey::market_listing_listings_release_stats_community_in_wantlist:
		RESULT.listings.back().release.stats.community.in_wantlist = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_release_stats_community;
		break;
	case StateKey::market_listing_listings_original_price_curr_id:
		RESULT.listings.back().original_price_.curr_id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_original_price;
		break;
	case StateKey::market_listing_listings_original_price_value:
		RESULT.listings.back().original_price_.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price;
		break;
	case StateKey::market_listing_listings_original_price_converted_curr_id:
		RESULT.listings.back().original_price_.converted.curr_id = str_to_int(value, length);
		m_state = StateKey::market_listing_listings_original_price_converted;
		break;
	case StateKey::market_listing_listings_original_price_converted_value:
		RESULT.listings.back().original_price_.converted.value = ::platform::string_t(value, length);
		m_state = StateKey::market_listing_listings_original_price_converted;
		break;
	case StateKey::market_listing_pagination_per_page:
		RESULT.pages.per_page = str_to_int(value, length);
		m_state = StateKey::market_listing_pagination;
		break;
	case StateKey::market_listing_pagination_items:
		RESULT.pages.items = str_to_int(value, length);
		m_state = StateKey::market_listing_pagination;
		break;
	case StateKey::market_listing_pagination_page:
		RESULT.pages.page = str_to_int(value, length);
		m_state = StateKey::market_listing_pagination;
		break;
	case StateKey::market_listing_pagination_pages:
		RESULT.pages.pages = str_to_int(value, length);
		m_state = StateKey::market_listing_pagination;
		break;
	default:
		return false;
	}
	return true;
}

bool market_get_parser::Number(int)
{
	return false;
}

bool market_get_parser::Double(double)
{
	return false;
}

bool market_get_parser::Null()
{
	switch(m_state){
		case StateKey::market_listing_listings:
			m_state = StateKey::market_listing;
			break;
		case StateKey::market_listing_listings_in_cart:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_allow_offers:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_audio:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_id:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_status:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_ships_from:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_uri:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_comments:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_sleeve_condition:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_resource_url:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_condition:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_posted:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_original_shipping_price:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_original_shipping_price_curr_id:
			m_state = StateKey::market_listing_listings_original_shipping_price;
			break;
		case StateKey::market_listing_listings_original_shipping_price_curr_abbr:
			m_state = StateKey::market_listing_listings_original_shipping_price;
			break;
		case StateKey::market_listing_listings_original_shipping_price_formatted:
			m_state = StateKey::market_listing_listings_original_shipping_price;
			break;
		case StateKey::market_listing_listings_original_shipping_price_value:
			m_state = StateKey::market_listing_listings_original_shipping_price;
			break;
		case StateKey::market_listing_listings_original_shipping_price_converted:
			m_state = StateKey::market_listing_listings_original_shipping_price;
			break;
		case StateKey::market_listing_listings_original_shipping_price_converted_curr_id:
			m_state = StateKey::market_listing_listings_original_shipping_price_converted;
			break;
		case StateKey::market_listing_listings_original_shipping_price_converted_curr_abbr:
			m_state = StateKey::market_listing_listings_original_shipping_price_converted;
			break;
		case StateKey::market_listing_listings_original_shipping_price_converted_formatted:
			m_state = StateKey::market_listing_listings_original_shipping_price_converted;
			break;
		case StateKey::market_listing_listings_original_shipping_price_converted_value:
			m_state = StateKey::market_listing_listings_original_shipping_price_converted;
			break;
		case StateKey::market_listing_listings_price:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_price_value:
			m_state = StateKey::market_listing_listings_price;
			break;
		case StateKey::market_listing_listings_price_currency:
			m_state = StateKey::market_listing_listings_price;
			break;
		case StateKey::market_listing_listings_shipping_price:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_shipping_price_currency:
			m_state = StateKey::market_listing_listings_shipping_price;
			break;
		case StateKey::market_listing_listings_shipping_price_value:
			m_state = StateKey::market_listing_listings_shipping_price;
			break;
		case StateKey::market_listing_listings_seller:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_seller_id:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_uid:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_username:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_url:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_html_url:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_shipping:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_payment:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_avatar_url:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_resource_url:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_stats:
			m_state = StateKey::market_listing_listings_seller;
			break;
		case StateKey::market_listing_listings_seller_stats_total:
			m_state = StateKey::market_listing_listings_seller_stats;
			break;
		case StateKey::market_listing_listings_seller_stats_rating:
			m_state = StateKey::market_listing_listings_seller_stats;
			break;
		case StateKey::market_listing_listings_seller_stats_stars:
			m_state = StateKey::market_listing_listings_seller_stats;
			break;
		case StateKey::market_listing_listings_release:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_release_id:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_year:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_description:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_format:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_catalog_number:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_artist:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_title:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_resource_url:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_thumbnail:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_images:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_images_height:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_images_width:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_images_uri:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_images_resource_url:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_images_type:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_images_uri150:
			m_state = StateKey::market_listing_listings_release_images;
			break;
		case StateKey::market_listing_listings_release_stats:
			m_state = StateKey::market_listing_listings_release;
			break;
		case StateKey::market_listing_listings_release_stats_user:
			m_state = StateKey::market_listing_listings_release_stats;
			break;
		case StateKey::market_listing_listings_release_stats_user_in_collection:
			m_state = StateKey::market_listing_listings_release_stats_user;
			break;
		case StateKey::market_listing_listings_release_stats_user_in_wantlist:
			m_state = StateKey::market_listing_listings_release_stats_user;
			break;
		case StateKey::market_listing_listings_release_stats_community:
			m_state = StateKey::market_listing_listings_release_stats;
			break;
		case StateKey::market_listing_listings_release_stats_community_in_collection:
			m_state = StateKey::market_listing_listings_release_stats_community;
			break;
		case StateKey::market_listing_listings_release_stats_community_in_wantlist:
			m_state = StateKey::market_listing_listings_release_stats_community;
			break;
		case StateKey::market_listing_listings_original_price:
			m_state = StateKey::market_listing_listings;
			break;
		case StateKey::market_listing_listings_original_price_curr_id:
			m_state = StateKey::market_listing_listings_original_price;
			break;
		case StateKey::market_listing_listings_original_price_curr_abbr:
			m_state = StateKey::market_listing_listings_original_price;
			break;
		case StateKey::market_listing_listings_original_price_formatted:
			m_state = StateKey::market_listing_listings_original_price;
			break;
		case StateKey::market_listing_listings_original_price_value:
			m_state = StateKey::market_listing_listings_original_price;
			break;
		case StateKey::market_listing_listings_original_price_converted:
			m_state = StateKey::market_listing_listings_original_price;
			break;
		case StateKey::market_listing_listings_original_price_converted_curr_id:
			m_state = StateKey::market_listing_listings_original_price_converted;
			break;
		case StateKey::market_listing_listings_original_price_converted_curr_abbr:
			m_state = StateKey::market_listing_listings_original_price_converted;
			break;
		case StateKey::market_listing_listings_original_price_converted_formatted:
			m_state = StateKey::market_listing_listings_original_price_converted;
			break;
		case StateKey::market_listing_listings_original_price_converted_value:
			m_state = StateKey::market_listing_listings_original_price_converted;
			break;
		case StateKey::market_listing_pagination:
			m_state = StateKey::market_listing;
			break;
		case StateKey::market_listing_pagination_per_page:
			m_state = StateKey::market_listing_pagination;
			break;
		case StateKey::market_listing_pagination_items:
			m_state = StateKey::market_listing_pagination;
			break;
		case StateKey::market_listing_pagination_page:
			m_state = StateKey::market_listing_pagination;
			break;
		case StateKey::market_listing_pagination_pages:
			m_state = StateKey::market_listing_pagination;
			break;
		case StateKey::market_listing_pagination_urls:
			m_state = StateKey::market_listing_pagination;
			break;
		case StateKey::market_listing_pagination_urls_next:
			m_state = StateKey::market_listing_pagination_urls;
			break;
		case StateKey::market_listing_pagination_urls_last:
			m_state = StateKey::market_listing_pagination_urls;
			break;
		case StateKey::market_listing_pagination_urls_first:
			m_state = StateKey::market_listing_pagination_urls;
			break;
		case StateKey::market_listing_pagination_urls_prev:
			m_state = StateKey::market_listing_pagination_urls;
			break;
	}
	return true;
}
bool market_get_parser::Key(const Ch* str, rapidjson::SizeType length, bool copy)
{
	switch(m_state){
	case StateKey::market_listing_listings_original_shipping_price_converted:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_converted_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_converted_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_converted_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_converted_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_original_shipping_price:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_value;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("converted")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price_converted;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_price:
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_price_value;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("currency")) == 0){
			m_state = StateKey::market_listing_listings_price_currency;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_shipping_price:
		if(length == 8 && platform::strcmp(str, STR("currency")) == 0){
			m_state = StateKey::market_listing_listings_shipping_price_currency;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_shipping_price_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_seller_stats:
		if(length == 5 && platform::strcmp(str, STR("total")) == 0){
			m_state = StateKey::market_listing_listings_seller_stats_total;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("rating")) == 0){
			m_state = StateKey::market_listing_listings_seller_stats_rating;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stars")) == 0){
			m_state = StateKey::market_listing_listings_seller_stats_stars;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_seller:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::market_listing_listings_seller_id;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uid")) == 0){
			m_state = StateKey::market_listing_listings_seller_uid;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("username")) == 0){
			m_state = StateKey::market_listing_listings_seller_username;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("url")) == 0){
			m_state = StateKey::market_listing_listings_seller_url;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("html_url")) == 0){
			m_state = StateKey::market_listing_listings_seller_html_url;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("shipping")) == 0){
			m_state = StateKey::market_listing_listings_seller_shipping;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("payment")) == 0){
			m_state = StateKey::market_listing_listings_seller_payment;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("avatar_url")) == 0){
			m_state = StateKey::market_listing_listings_seller_avatar_url;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::market_listing_listings_seller_resource_url;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stats")) == 0){
			m_state = StateKey::market_listing_listings_seller_stats;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_release_images:
		if(length == 6 && platform::strcmp(str, STR("height")) == 0){
			m_state = StateKey::market_listing_listings_release_images_height;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("width")) == 0){
			m_state = StateKey::market_listing_listings_release_images_width;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::market_listing_listings_release_images_uri;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::market_listing_listings_release_images_resource_url;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("type")) == 0){
			m_state = StateKey::market_listing_listings_release_images_type;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("uri150")) == 0){
			m_state = StateKey::market_listing_listings_release_images_uri150;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_release_stats_user:
		if(length == 13 && platform::strcmp(str, STR("in_collection")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_user_in_collection;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("in_wantlist")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_user_in_wantlist;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_release_stats_community:
		if(length == 13 && platform::strcmp(str, STR("in_collection")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_community_in_collection;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("in_wantlist")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_community_in_wantlist;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_release_stats:
		if(length == 4 && platform::strcmp(str, STR("user")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_user;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("community")) == 0){
			m_state = StateKey::market_listing_listings_release_stats_community;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_release:
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::market_listing_listings_release_id;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("year")) == 0){
			m_state = StateKey::market_listing_listings_release_year;
		}
		else
		if(length == 11 && platform::strcmp(str, STR("description")) == 0){
			m_state = StateKey::market_listing_listings_release_description;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("format")) == 0){
			m_state = StateKey::market_listing_listings_release_format;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("catalog_number")) == 0){
			m_state = StateKey::market_listing_listings_release_catalog_number;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("artist")) == 0){
			m_state = StateKey::market_listing_listings_release_artist;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("title")) == 0){
			m_state = StateKey::market_listing_listings_release_title;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::market_listing_listings_release_resource_url;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("thumbnail")) == 0){
			m_state = StateKey::market_listing_listings_release_thumbnail;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("images")) == 0){
			m_state = StateKey::market_listing_listings_release_images;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("stats")) == 0){
			m_state = StateKey::market_listing_listings_release_stats;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_original_price_converted:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::market_listing_listings_original_price_converted_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::market_listing_listings_original_price_converted_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::market_listing_listings_original_price_converted_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_original_price_converted_value;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings_original_price:
		if(length == 7 && platform::strcmp(str, STR("curr_id")) == 0){
			m_state = StateKey::market_listing_listings_original_price_curr_id;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("curr_abbr")) == 0){
			m_state = StateKey::market_listing_listings_original_price_curr_abbr;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("formatted")) == 0){
			m_state = StateKey::market_listing_listings_original_price_formatted;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("value")) == 0){
			m_state = StateKey::market_listing_listings_original_price_value;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("converted")) == 0){
			m_state = StateKey::market_listing_listings_original_price_converted;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_listings:
		if(length == 7 && platform::strcmp(str, STR("in_cart")) == 0){
			m_state = StateKey::market_listing_listings_in_cart;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("allow_offers")) == 0){
			m_state = StateKey::market_listing_listings_allow_offers;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("audio")) == 0){
			m_state = StateKey::market_listing_listings_audio;
		}
		else
		if(length == 2 && platform::strcmp(str, STR("id")) == 0){
			m_state = StateKey::market_listing_listings_id;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("status")) == 0){
			m_state = StateKey::market_listing_listings_status;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("ships_from")) == 0){
			m_state = StateKey::market_listing_listings_ships_from;
		}
		else
		if(length == 3 && platform::strcmp(str, STR("uri")) == 0){
			m_state = StateKey::market_listing_listings_uri;
		}
		else
		if(length == 8 && platform::strcmp(str, STR("comments")) == 0){
			m_state = StateKey::market_listing_listings_comments;
		}
		else
		if(length == 16 && platform::strcmp(str, STR("sleeve_condition")) == 0){
			m_state = StateKey::market_listing_listings_sleeve_condition;
		}
		else
		if(length == 12 && platform::strcmp(str, STR("resource_url")) == 0){
			m_state = StateKey::market_listing_listings_resource_url;
		}
		else
		if(length == 9 && platform::strcmp(str, STR("condition")) == 0){
			m_state = StateKey::market_listing_listings_condition;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("posted")) == 0){
			m_state = StateKey::market_listing_listings_posted;
		}
		else
		if(length == 23 && platform::strcmp(str, STR("original_shipping_price")) == 0){
			m_state = StateKey::market_listing_listings_original_shipping_price;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("price")) == 0){
			m_state = StateKey::market_listing_listings_price;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("shipping_price")) == 0){
			m_state = StateKey::market_listing_listings_shipping_price;
		}
		else
		if(length == 6 && platform::strcmp(str, STR("seller")) == 0){
			m_state = StateKey::market_listing_listings_seller;
		}
		else
		if(length == 7 && platform::strcmp(str, STR("release")) == 0){
			m_state = StateKey::market_listing_listings_release;
		}
		else
		if(length == 14 && platform::strcmp(str, STR("original_price")) == 0){
			m_state = StateKey::market_listing_listings_original_price;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_pagination_urls:
		if(length == 4 && platform::strcmp(str, STR("next")) == 0){
			m_state = StateKey::market_listing_pagination_urls_next;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("last")) == 0){
			m_state = StateKey::market_listing_pagination_urls_last;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("first")) == 0){
			m_state = StateKey::market_listing_pagination_urls_first;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("prev")) == 0){
			m_state = StateKey::market_listing_pagination_urls_prev;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing_pagination:
		if(length == 8 && platform::strcmp(str, STR("per_page")) == 0){
			m_state = StateKey::market_listing_pagination_per_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("items")) == 0){
			m_state = StateKey::market_listing_pagination_items;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("page")) == 0){
			m_state = StateKey::market_listing_pagination_page;
		}
		else
		if(length == 5 && platform::strcmp(str, STR("pages")) == 0){
			m_state = StateKey::market_listing_pagination_pages;
		}
		else
		if(length == 4 && platform::strcmp(str, STR("urls")) == 0){
			m_state = StateKey::market_listing_pagination_urls;
		}
		else {
			return false;
		}
		break;
	case StateKey::market_listing:
		if(length == 8 && platform::strcmp(str, STR("listings")) == 0){
			m_state = StateKey::market_listing_listings;
		}
		else
		if(length == 10 && platform::strcmp(str, STR("pagination")) == 0){
			m_state = StateKey::market_listing_pagination;
		}
		else {
			return false;
		}
		break;
	}
	return true;
}
bool market_get_parser::StartArray()
{
	return true;
}
bool market_get_parser::EndArray(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::market_listing_listings:
		m_state = StateKey::market_listing;
		break;
	case StateKey::market_listing_listings_release_images:
		m_state = StateKey::market_listing_listings_release;
		break;
	}
	return true;
}

bool market_get_parser::StartObject()
{
	switch(m_state){
	case StateKey::market_listing_listings:
		RESULT.listings.emplace_back();
		break;
	case StateKey::market_listing_listings_release_images:
		RESULT.listings.back().release.images.emplace_back();
		break;
	}
	return true;
}

bool market_get_parser::EndObject(rapidjson::SizeType memberCount)
{
	switch(m_state){
	case StateKey::market_listing_listings_original_shipping_price:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_original_shipping_price_converted:
		m_state = StateKey::market_listing_listings_original_shipping_price;
		break;
	case StateKey::market_listing_listings_price:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_shipping_price:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_seller:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_seller_stats:
		m_state = StateKey::market_listing_listings_seller;
		break;
	case StateKey::market_listing_listings_release:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_release_stats:
		m_state = StateKey::market_listing_listings_release;
		break;
	case StateKey::market_listing_listings_release_stats_user:
		m_state = StateKey::market_listing_listings_release_stats;
		break;
	case StateKey::market_listing_listings_release_stats_community:
		m_state = StateKey::market_listing_listings_release_stats;
		break;
	case StateKey::market_listing_listings_original_price:
		m_state = StateKey::market_listing_listings;
		break;
	case StateKey::market_listing_listings_original_price_converted:
		m_state = StateKey::market_listing_listings_original_price;
		break;
	case StateKey::market_listing_pagination:
		m_state = StateKey::market_listing;
		break;
	case StateKey::market_listing_pagination_urls:
		m_state = StateKey::market_listing_pagination;
		break;
	}
	return true;
}

market_get_parser::market_get_parser()
{
	m_state = StateKey::market_listing;
}

} // namespace discogs
} // namespace parser
