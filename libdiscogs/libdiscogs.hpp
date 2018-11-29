// TODO, I don't think I want libdiscogs itself using platform.
// I'm including it to get the platform::string_t definition, but
// there should be no other dependencies.  At the moment the only
// dependencies I want to keep around are rapidjson and cpprestsdk
#include "libplatform/platform.hpp"

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

// Since this is using the cpprestsdk, this api can throw any
// of the exceptions that the cpprestsdk uses.  I'm going to need
// to document those somehow.

#include "include/folder_releases.hpp"
#include "include/collection.hpp"
#include "include/wantlist.hpp"
#include "include/release.hpp"
#include "include/master.hpp"
#include "include/identity.hpp"
#include "include/folder_response.hpp"
#include "include/folder_collection_releases.hpp"
#include "include/collection_add_response.hpp"
#include "include/search.hpp"
#include "include/market_get.hpp"

#include "liboauth1/oauth1_data.hpp"

/*
	The discogs REST api will return a pplx::task_from_result
	object which contains a raw pointer to the data being managed.

	This is because the pplx library can't deal with move only types
	and therefore cannot return a std::unique_ptr.

	I do not want to force the user of this API to have to take a
	std::shared_ptr or be forced to copy large objects.

	Therefore it's reccomended you wrap the raw ptr from this API
	into either a std::unique_ptr or std::shared_ptr as you prefer.

	This is also bad, because it forces the user to care about the
	result from task.get().  If it's not handled then there
	will be a memory leak.
*/

namespace discogs {

/*
	This is a helper function to reduce the amount of typing
	needed to make a unique_ptr from a raw pointer.
	I would have thought that the unique_ptr template class could
	infer the type of T from the argument, but that seems to not
	be the case.
*/

template<typename T>
static std::unique_ptr<T> unique(T *t)
{
	return std::unique_ptr<T>(t);
}

class rest_private;

class rest {
public:
	rest(
		const platform::string_t &user_agent,
		const platform::string_t &base_url = STR("https://api.discogs.com")
	);
	~rest();

	rest(const rest &rhs) = delete;
	rest& operator=(const rest &rhs) = delete;

	rest(rest &&rhs) noexcept = delete;
	rest& operator=(rest &&rhs) noexcept = delete;

	int per_page() const;
	void set_per_page(int per_page);

	const static platform::string_t empty;

	typedef std::vector<std::pair<platform::string_t,platform::string_t>> string_list;

	// ---- DATABASE ----

	// RELEASE
	// GET /releases/{release_id}{?curr_abbr}
	// https://www.discogs.com/developers/#page:database,header:database-release-get
	// Get a release
	pplx::task<discogs::parser::release *>
	release(int release_id);

	// MASTER RELEASE
	// GET /masters/{master_id}
	// https://www.discogs.com/developers/#page:database,header:database-master-release
	// Get a master release

	pplx::task<discogs::result::master *>
	master(int master_id);

	// SEARCH
	// GET /database/search?q=
	// https://www.discogs.com/developers/#page:database,header:database-search
	// Issue a search query

	// To use this API please read the discogs documentation
	// Supply a vector of string pairs of "argument", "value"
	// as described in the API docs
	pplx::task<discogs::result::search_results *>
	search(
		const std::vector<std::pair<platform::string_t,platform::string_t>> &terms,
		int page_id = -1
	);


	// ---- END DATABASE ----
	// ---- MARKETPLACE ----

	// INVENTORY
	// GET /users/{username}/inventory{?status,sort,sort_order}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-inventory-get
	// Get a seller’s inventory
	pplx::task<discogs::parser::market_listing*>
	market_get(
		const platform::string_t &username,
		const platform::string_t &status = empty,
		const platform::string_t &sort = empty,
		const platform::string_t &sort_order = empty
	);

	// LISTING
	// GET /marketplace/listings/{listing_id}{?curr_abbr}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-listing-get
	// The Listing resource allows you to view Marketplace listings

	pplx::task<void*>
	market_listing(
		int listing_id,
		const platform::string_t &curr_abbr = empty
	);

	// LISTING
	// POST /marketplace/listings/{listing_id}{?curr_abbr}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-listing-post
	// Edit the data associated with a listing

	// TODO: add the extra arguments
	pplx::task<void*>
	market_listing_update(
		int listing_id,
		int release_id,
		const platform::string_t &condition,
		const platform::string_t &price
	);

	// LISTING
	// DELETE /marketplace/listings/{listing_id}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-listing-delete
	// Permanently remove a listing from the Marketplace
	pplx::task<void*>
	market_listing_delete(int listing_id);

	// NEW LISTING
	// POST /marketplace/listings{?release_id,condition,sleeve_condition,price,comments,allow_offers,status,external_id,location,weight,format_quantity}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-new-listing-post
	// Create a Marketplace listing
	pplx::task<void*>
	market_listing_new(
		int release_id,
		const platform::string_t &condition,
		const platform::string_t &price
		// TODO extra arguments
	);

	// ORDER
	// GET /marketplace/orders/{order_id}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-order-get
	// View the data associated with an order
	pplx::task<void*>
	market_order(int order_id);

	// ORDER
	// POST /marketplace/orders/{order_id}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-order-post
	// Edit the data associated with an order
	pplx::task<void*>
	market_order_update(
		int order_id
		// TODO extra arguments
	);

	// LIST ORDERS
	// GET /marketplace/orders{?status,sort,sort_order}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-list-orders-get
	// Returns a list of the authenticated user’s orders
	pplx::task<void*>
	market_list_orders(
		const platform::string_t &status = empty,
		const platform::string_t &sort = empty,
		const platform::string_t &sort_order = empty
	);

	// LIST ORDER MESSAGES
	// GET /marketplace/orders/{order_id}/messages
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-list-order-messages-get
	// Returns a list of the order’s messages with the most recent first
	pplx::task<void*>
	market_list_order_messages(int order_id);

	// LIST ORDER MESSAGES
	// POST /marketplace/orders/{order_id}/messages
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-list-order-messages-post
	// Adds a new message to the order’s message log
	// While message and status are each optional, one or both must be present
	pplx::task<void*>
	market_list_order_messages(
		int order_id,
		const platform::string_t &message = empty,
		const platform::string_t &status = empty
	);

	// FEE
	// GET /marketplace/fee/{price}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-fee-get
	// The Fee resource allows you to quickly calculate the fee for selling an item on the Marketplace
	pplx::task<void*>
	market_fee(const platform::string_t &price);

	// FEE WITH CURRENCY
	// GET /marketplace/fee/{price}/{currency}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-fee-with-currency-get
	// The Fee resource allows you to quickly calculate the fee for selling an item on the Marketplace given a particular currency
	pplx::task<void*>
	market_fee_currency(
		const platform::string_t &price,
		const platform::string_t &currency
	);

	// PRICE SUGGESTIONS
	// GET /marketplace/price_suggestions/{release_id}
	// https://www.discogs.com/developers/#page:marketplace,header:marketplace-price-suggestions-get
	// Retrieve price suggestions for the provided Release ID
	pplx::task<void*>
	market_price_suggestions(int release_id);


	// ---- END MARKETPLACE ----
	// ---- COLLECTION ----

	// COLLECTION
	// GET /users/{username}/collection/folders
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-get
	// Retrieve a list of folders in a user’s collection
	pplx::task<discogs::parser::folder_list *>
	collection_folders(const platform::string_t &username);

	// COLLECTION
	// POST /users/{username}/collection/folders
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-post
	// Create a new folder in a user’s collection
	pplx::task<discogs::parser::folder_response *>
	collection_folder_add(
		const platform::string_t &username,
		const platform::string_t &folder_name
	);

	// COLLECTION FOLDER
	// GET /users/{username}/collection/folders/{folder_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-folder-get
	// Retrieve metadata about a folder in a user’s collection
	pplx::task<discogs::parser::folder_response*>
	collection_folder(
		const platform::string_t &username,
		int folder_id
	);

	// COLLECTION FOLDER
	// POST /users/{username}/collection/folders/{folder_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-folder-post
	// Edit a folder’s metadata. Folders 0 and 1 cannot be renamed
	pplx::task<void*>
	collection_folder_update(
		const platform::string_t &username,
		int folder_id
	);

	// COLLECTION FOLDER
	// DELETE /users/{username}/collection/folders/{folder_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-folder-delete
	// Delete a folder from a user’s collection. A folder must be empty before it can be deleted.
	pplx::task<bool>
	collection_folder_delete(
		const platform::string_t &username,
		int folder_id
	);

	// COLLECTION ITEMS BY RELEASE
	// GET /users/{username}/collection/releases/{release_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-items-by-release-get
	// View the user’s collection folders which contain a specified release
	pplx::task<discogs::parser::collection_release*>
	collection_releases(
		const platform::string_t &username,
		int release_id
	);

	// COLLECTION ITEMS BY FOLDER
	// GET /users/{username}/collection/folders/{folder_id}/releases
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-items-by-folder-get
	// Returns the list of item in a folder in a user’s collection
	pplx::task<discogs::parser::folder_releases *>
	collection_folder_releases(
		const platform::string_t &username,
		const platform::string_t &folder_id,
		int page_id = 1
	);

	// ADD TO COLLECTION FOLDER
	// POST /users/{username}/collection/folders/{folder_id}/releases/{release_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-add-to-collection-folder-post
	// Add a release to a folder in a user’s collection
	pplx::task<discogs::parser::collection_add_response *>
	collection_add_to_folder(
		const platform::string_t &username,
		int folder_id,
		int release_id
	);

	// CHANGE RATING OF RELEASE
	// POST /users/{username}/collection/folders/{folder_id}/releases/{release_id}/instances/{instance_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-change-rating-of-release-post
	// Change the rating on a release and/or move the instance to another folder.
	pplx::task<bool>
	collection_change_rating_of_release(
		const platform::string_t &username,
		int folder_id,
		int release_id,
		int instance_id,
		int rating = -1,
		int new_folder_id = -1
	);

	// DELETE INSTANCE FROM FOLDER
	// DELETE /users/{username}/collection/folders/{folder_id}/releases/{release_id}/instances/{instance_id}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-delete-instance-from-folder-delete
	// Remove an instance of a release from a user’s collection folder
	pplx::task<bool>
	collection_delete_instance_from_folder(
		const platform::string_t &username,
		int folder_id,
		int release_id,
		int instance_id
	);

	// LIST CUSTOM FIELDS
	// GET /users/{username}/collection/fields
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-list-custom-fields-get
	// Retrieve a list of user-defined collection notes fields
	pplx::task<void*>
	collection_list_custom_fields(
		const platform::string_t &username
	);

	// EDIT FIELDS INSTANCE
	// POST /users/{username}/collection/folders/{folder_id}/releases/{release_id}/instances/{instance_id}/fields/{field_id}{?value}
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-edit-fields-instance-post
	// Change the value of a notes field on a particular instance
	pplx::task<void*>
	collection_edit_fields_instance(
		const platform::string_t &username,
		const platform::string_t &value,
		int folder_id,
		int release_id,
		int instance_id,
		int field_id
	);

	// COLLECTION VALUE
	// GET /users/{username}/collection/value
	// https://www.discogs.com/developers/#page:user-collection,header:user-collection-collection-value-get
	// Returns the minimum, median, and maximum value of a user’s collection
	pplx::task<void*>
	collection_value(
		const platform::string_t &username
	);

	// ---- END COLLECTION ----

	// ---- WANTLIST ----

	// WANTLIST
	// GET /users/{username}/wants
	// https://www.discogs.com/developers/#page:user-wantlist,header:user-wantlist-wantlist-get
	// Returns the list of releases in a user’s wantlist
	pplx::task<discogs::parser::wantlist *>
	wantlist(
		const platform::string_t &username,
		int page_id = 1
	);

	// ADD TO WANTLIST
	// GET /users/{username}/wants/{release_id}{?notes,rating}
	// https://www.discogs.com/developers/#page:user-wantlist,header:user-wantlist-add-to-wantlist-put
	// Add a release to a user’s wantlist
	pplx::task<bool>
	wantlist_add(
		int release_id,
		const platform::string_t &username
	);

	// ADD TO WANTLIST
	// POST /users/{username}/wants/{release_id}{?notes,rating}
	// https://www.discogs.com/developers/#page:user-wantlist,header:user-wantlist-add-to-wantlist-post
	// Update notes or rating on the wantlist
	pplx::task<bool>
	wantlist_update(
		int release_id,
		const platform::string_t &username,
		const platform::string_t &notes,
		int rating = -1
	);

	// DELETE WANTLIST ITEM
	// DELETE /users/{username}/wants/{release_id}{?notes,rating}
	// https://www.discogs.com/developers/#page:user-wantlist,header:user-wantlist-add-to-wantlist-delete
	// Delete a release from the wantlist.
	pplx::task<bool>
	wantlist_delete(
		int release_id,
		const platform::string_t &username
	);

	// ---- END WANTLIST ----

	// ---- IDENTITY ----
	// IDENTITY
	// GET /oauth/identity
	// https://www.discogs.com/developers/#page:user-identity,header:user-identity-identity-get
	// Retrieve basic information about the authenticated user.

	pplx::task<discogs::parser::identity *>
	identity();

	// ---- END IDENTITY ----

	// Configuration data for the OAuth system
	// Supply the filled data struct, along with
	// the logged in users tokens.
	void oauth_configure(
		const discogs::oauth1_data &data,
		const platform::string_t &access_token,
		const platform::string_t &secret_token
	);

	// Just download a URL without processing, store the body as
	// a string_t.  url_path is the URL path after the domain.
	// EG if you want http://api.domain.com/foo/bar/baz
	// then set url_path to foo/bar/baz
	pplx::task<platform::string_t>
	download_url(const platform::string_t &url_path);

private:
	std::unique_ptr<discogs::rest_private> m_private;
};

}
