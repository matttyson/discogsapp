#pragma once

#include "platform.hpp"

namespace platform {

class exception {
public:
	exception():message(nullptr){}
	exception(const platform::char_t *message_):message(message_){}

	const platform::char_t* what() { return message; }
protected:
	const platform::char_t *message;
};

class file_error : public ::platform::exception {
public:
	file_error():exception(){}
	file_error(const platform::char_t *message):exception(message){}
};

}
