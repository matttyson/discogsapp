
#include "porting.h"

#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>

// TODO: work out how to remove the dependecy on http_client.h  pimpl idiom?

#include "include/folder_releases.hpp"
#include "include/collection.hpp"
#include "include/wantlist.hpp"


namespace discogs {

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

	// COLLECTION
	pplx::task<discogs::parser::collection::container>
	collection(const string_t &username);

	// COLLECTION ITEMS BY FOLDER
	pplx::task<discogs::parser::folder_releases::container>
	folder_releases(
		const string_t &username,
		const string_t &folder_id,
		int page_id = 1
	);

	// Get Wantlist
	pplx::task<discogs::parser::wantlist::container>
	wantlist(
		const string_t &username,
		int page_id = 1
	);

	// Add to wantlist
	pplx::task<bool>
	add_wantlist(
		int release_id,
		const string_t &username
	);

	// Update notes or rating on the wantlist
	pplx::task<bool>
	update_wantlist(
		int release_id,
		const string_t &username,
		const string_t &notes,
		int rating = -1
	);

	// Delete a release from the wantlist.
	pplx::task<bool>
	delete_wantlist(
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
