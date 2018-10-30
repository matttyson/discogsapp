#include "liboauth1/oauth1_data.hpp"

// Note to self - I've set git to ignore this file so that I don't commit
// API keys to the repo.

// git update-index --assume-unchanged
// git update-index --no-assume-unchanged

discogs::oauth1_data get_oauth_data()
{
	return discogs::oauth1_data {
		STR(""),
		STR(""),
		STR("https://api.discogs.com/oauth/request_token"),
		STR("https://www.discogs.com/oauth/authorize"),
		STR("https://api.discogs.com/oauth/access_token"),
		STR("http://localhost:32000")
	};
}
