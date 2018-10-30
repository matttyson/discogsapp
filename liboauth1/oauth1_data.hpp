#pragma once

#include "porting.h"

namespace discogs {

struct oauth1_data {
	oauth1_data(
		const string_t &consumer_key_,
		const string_t &consumer_secret_,
		const string_t &temp_endpoint_,
		const string_t &auth_endpoint_,
		const string_t &token_endpoint_,
		const string_t &callback_uri_
	) :
		consumer_key(consumer_key_),
		consumer_secret(consumer_secret_),
		temp_endpoint(temp_endpoint_),
		auth_endpoint(auth_endpoint_),
		token_endpoint(token_endpoint_),
		callback_uri(callback_uri_)
	{}

	const string_t consumer_key;
	const string_t consumer_secret;
	const string_t temp_endpoint;
	const string_t auth_endpoint;
	const string_t token_endpoint;
	const string_t callback_uri;
};

}
