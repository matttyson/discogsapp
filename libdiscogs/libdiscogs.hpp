// TODO, I don't think I want libdiscogs itself using platform.
// I'm including it to get the platform::string_t definition, but
// there should be no other dependencies.  At the moment the only
// dependencies I want to kee around are rapidjson and cpprestsdk
#include "libplatform/platform.hpp"

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

// I want to remove http_client.h so the cpprestsdk isn't visible outside this
// header file.  I need to create a new set of exceptions so the cpprestk
// exception defintions aren't needed.

#include "include/folder_releases.hpp"
#include "include/collection.hpp"
#include "include/wantlist.hpp"
#include "include/release.hpp"
#include "include/identity.hpp"
#include "include/folder_response.hpp"
#include "include/folder_collection_releases.hpp"
#include "include/collection_add_response.hpp"

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

	// ---- DATABASE ----

	// RELEASE
	// GET /releases/{release_id}{?curr_abbr}
	// https://www.discogs.com/developers/#page:database,header:database-release-get
	// Get a release
	pplx::task<discogs::parser::release *>
	release(int release_id);

	// ---- END DATABASE ----
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
