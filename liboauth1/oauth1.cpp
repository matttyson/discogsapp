#include "oauth1.hpp"
#include "oauth1_listener.hpp"

#include <cpprest/oauth1.h>


namespace discogs {
class oauth1_data_private {
public:
	oauth1_data_private(const discogs::oauth1_data &data_, browser_function func_)
		:oauth1_config(
			data_.consumer_key,
			data_.consumer_secret,
			data_.temp_endpoint,
			data_.auth_endpoint,
			data_.token_endpoint,
			data_.callback_uri,
			web::http::oauth1::experimental::oauth1_methods::plaintext
		),
		listener(data_.callback_uri, oauth1_config),
		data(data_),
		func(func_)
	{}

	web::http::oauth1::experimental::oauth1_config oauth1_config;
	oauth1_code_listener listener;
	discogs::oauth1_data data;
	browser_function func;
};
}

discogs::oauth1::oauth1(const discogs::oauth1_data &data, browser_function func)
	:m_data(new discogs::oauth1_data_private(data, func))
{

}

discogs::oauth1::~oauth1()
{
}


pplx::task<bool> discogs::oauth1::authenticate()
{
	utility::string_t auth_uri = m_data->oauth1_config.build_authorization_uri().get();

	m_data->func(auth_uri);

	return m_data->listener.listen_for_code();
}

platform::string_t discogs::oauth1::access_token()
{
	return m_data->oauth1_config.token().access_token();
}

platform::string_t discogs::oauth1::secret()
{
	return m_data->oauth1_config.token().secret();
}
