#include "oauth1_listener.hpp"

oauth1_code_listener::oauth1_code_listener(
	web::http::uri listen_uri,
	web::http::oauth1::experimental::oauth1_config &config
)
	:m_listener(new web::http::experimental::listener::http_listener(listen_uri)),
	m_config(config)
{
	m_listener->support([this](web::http::http_request request) -> void {
		if (request.request_uri().path() == U("/") && request.request_uri().query() != U("")){
			m_resplock.lock();

			m_config.token_from_redirected_uri(request.request_uri()).then([this, request](pplx::task<void> token_task) -> void {
				try {
					token_task.wait();
					m_tce.set(true);
				}
				// TODO: Do we want to propagate this exception or somehow
				// provide an error message to the user?
				catch(const web::http::oauth1::experimental::oauth1_exception &e) {
					m_tce.set(false);
				}
			});

			request.reply(web::http::status_codes::OK, U("Ok."));

			m_resplock.unlock();
		}
		else {
			request.reply(web::http::status_codes::NotFound, U("Not Found."));
		}
	});

	m_listener->open().wait();
}

oauth1_code_listener::~oauth1_code_listener()
{
	m_listener->close().wait();
}


pplx::task<bool> oauth1_code_listener::listen_for_code()
{
	return pplx::create_task(m_tce);
}
