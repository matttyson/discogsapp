
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

	int per_page() const;
	void set_per_page(int per_page);

	// RELEASE
	pplx::task<discogs::parser::release *>
	release(int release_id);

	// ---- COLLECTION ----

	// COLLECTION
	// GET /users/{username}/collection/folders
	pplx::task<discogs::parser::folder_list *>
	collection_folders(const platform::string_t &username);


	// COLLECTION ITEMS BY FOLDER
	// GET /users/{username}/collection/folders/{folder_id}/releases
	pplx::task<discogs::parser::folder_releases *>
	collection_folder_releases(
		const platform::string_t &username,
		const platform::string_t &folder_id,
		int page_id = 1
	);


	// ---- END COLLECTION ----

	// ---- WANTLIST ----

	// Get Wantlist
	pplx::task<discogs::parser::wantlist *>
	wantlist(
		const platform::string_t &username,
		int page_id = 1
	);

	// Add to wantlist
	pplx::task<bool>
	wantlist_add(
		int release_id,
		const platform::string_t &username
	);

	// Update notes or rating on the wantlist
	pplx::task<bool>
	wantlist_update(
		int release_id,
		const platform::string_t &username,
		const platform::string_t &notes,
		int rating = -1
	);

	// Delete a release from the wantlist.
	pplx::task<bool>
	wantlist_delete(
		int release_id,
		const platform::string_t &username
	);

	// ---- END WANTLIST ----

	// Configuration data for the OAuth system
	// Supply the filled data struct, along with
	// the logged in users tokens.
	void oauth_configure(
		const discogs::oauth1_data &data,
		const platform::string_t &access_token,
		const platform::string_t &secret_token
	);

	// Returns the identity of the user when logged in with oauth.
	pplx::task<discogs::parser::identity *>
	identity();

	// Just download a URL without processing, store the body as
	// a string_t.  url_path is the URL path after the domain.
	// EG if you want http://api.domain.com/foo/bar/baz
	// then set url_path to foo/bar/baz
	pplx::task<platform::string_t>
	download_url(const platform::string_t &url_path);

private:
	web::http::http_request create_request(
		const web::uri_builder &url,
		const web::http::method &method = web::http::methods::GET
	);

private:
	std::unique_ptr<discogs::rest_private> m_private;
};

}
