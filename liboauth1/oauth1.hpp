#pragma once

#include "libplatform/platform.hpp"

#include "oauth1_data.hpp"

#include <pplx/pplxtasks.h>
#include <memory>

// A function that will open the users default browser and load the given URL.
typedef void(*browser_function)(const platform::string_t &url) ;

namespace discogs {

class oauth1_data_private;

class oauth1 {
public:
	oauth1(const oauth1_data &data, browser_function browser);
	~oauth1();

	// Call this to do the authentication.
	// TODO: introduce some kind of timeout / cancellation
	// as this is a blocking operation.
	pplx::task<bool> authenticate();

	// If the operation was a success, we can call this to get
	// the result.
	platform::string_t access_token();
	platform::string_t secret();

private:
	std::unique_ptr<oauth1_data_private> m_data;
};

}

