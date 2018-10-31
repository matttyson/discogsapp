#pragma once

#include "libplatform/platform.hpp"

namespace discogs {

struct oauth1_data {
	oauth1_data(
		const platform::string_t &consumer_key_,
		const platform::string_t &consumer_secret_,
		const platform::string_t &temp_endpoint_,
		const platform::string_t &auth_endpoint_,
		const platform::string_t &token_endpoint_,
		const platform::string_t &callback_uri_
	) :
		consumer_key(consumer_key_),
		consumer_secret(consumer_secret_),
		temp_endpoint(temp_endpoint_),
		auth_endpoint(auth_endpoint_),
		token_endpoint(token_endpoint_),
		callback_uri(callback_uri_)
	{}

	const platform::string_t consumer_key;
	const platform::string_t consumer_secret;
	const platform::string_t temp_endpoint;
	const platform::string_t auth_endpoint;
	const platform::string_t token_endpoint;
	const platform::string_t callback_uri;
};

}
