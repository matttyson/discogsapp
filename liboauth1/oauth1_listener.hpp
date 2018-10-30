#pragma once

/*
	This object will start listening for an incoming http connection
	on the host and port provided.

	When the object is destroyed the connection will be closed.

	If the task object from listen_for_code() evaluates to true, then
	the config object will have the users oauth token details stored.

	Code adapted from Oauth1Client.cpp in the cpprestsdk samples directory
*/

#include <mutex>
#include <cpprest/http_listener.h>
#include <cpprest/oauth1.h>

class oauth1_code_listener {
public:
	oauth1_code_listener(
		web::http::uri listen_uri,
		web::http::oauth1::experimental::oauth1_config &config
	);
	~oauth1_code_listener();

	// Return a task that can be used to wait for the code.
	pplx::task<bool> listen_for_code();
private:
	std::unique_ptr<web::http::experimental::listener::http_listener> m_listener;
	web::http::oauth1::experimental::oauth1_config &m_config;
	pplx::task_completion_event<bool> m_tce;
	std::mutex m_resplock;
};

