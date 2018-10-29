
#include "porting.h"

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

// TODO: work out how to remove the dependecy on http_client.h  pimpl idiom?

#include "include/folder_releases.hpp"
#include "include/collection.hpp"
#include "include/wantlist.hpp"
#include "include/release.hpp"

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

class rest {
public:
	rest(
		const string_t &user_agent,
		const string_t &base_url = STR("https://api.discogs.com")
	);
	~rest();
	void set_session_key(const string_t &session_key);

	int per_page() const { return m_per_page; }
	void set_per_page(int per_page) { m_per_page = per_page; }

	// RELEASE
	pplx::task<discogs::parser::release *>
	release(int release_id);

	// COLLECTION
	pplx::task<discogs::parser::folder_list *>
	collection(const string_t &username);

	// COLLECTION ITEMS BY FOLDER
	pplx::task<discogs::parser::folder_releases *>
	folder_releases(
		const string_t &username,
		const string_t &folder_id,
		int page_id = 1
	);

	// Get Wantlist
	pplx::task<discogs::parser::wantlist *>
	wantlist(
		const string_t &username,
		int page_id = 1
	);

	// Add to wantlist
	pplx::task<bool>
	wantlist_add(
		int release_id,
		const string_t &username
	);

	// Update notes or rating on the wantlist
	pplx::task<bool>
	wantlist_update(
		int release_id,
		const string_t &username,
		const string_t &notes,
		int rating = -1
	);

	// Delete a release from the wantlist.
	pplx::task<bool>
	wantlist_delete(
		int release_id,
		const string_t &username
	);

private:
	web::http::http_request create_request(
		const web::uri_builder &url,
		const web::http::method &method = web::http::methods::GET
	);

private:
	int m_per_page;
	string_t m_user_agent;
	string_t m_session_key;
	web::http::client::http_client m_client;
};

}
