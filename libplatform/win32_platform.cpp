#include "platform.hpp"

#ifdef PLATFORM_WCHAR

#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

platform::string_t platform::to_string_t(const std::string &str)
{
	int rc = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), str.size(), NULL, 0);

	if (rc == 0) {
		throw std::runtime_error("Bad UTF-8 sequence in string");
	}

	std::wstring out(rc, '\0');

	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), str.size(), out.data(), out.size());

	return out;
}

platform::string_t platform::to_string_t(const char * str)
{
	size_t len = strlen(str);
	int rc = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, len, NULL, 0);

	if (rc == 0) {
		throw std::runtime_error("Bad UTF-8 sequence in string");
	}

	std::wstring out(rc, '\0');

	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, len, out.data(), out.size());

	return out;
}


#endif
