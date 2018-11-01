#include "platform.hpp"

#ifdef PLATFORM_WCHAR

#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

platform::string_t platform::to_string_t(const std::string &str)
{
	const DWORD str_size = static_cast<DWORD>(str.size());
	int rc = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), str_size, NULL, 0);

	if (rc == 0) {
		throw std::runtime_error("Bad UTF-8 sequence in string");
	}

	std::wstring out(rc, '\0');
	const DWORD out_size = static_cast<DWORD>(out.size());
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.c_str(), str_size, out.data(), out_size);

	return out;
}

platform::string_t platform::to_string_t(const char * str)
{
	const DWORD len = static_cast<DWORD>(strlen(str));
	int rc = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, len, NULL, 0);

	if (rc == 0) {
		throw std::runtime_error("Bad UTF-8 sequence in string");
	}

	std::wstring out(rc, '\0');
	const DWORD out_size = static_cast<DWORD>(out.size());
	MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str, len, out.data(), out_size);

	return out;
}


#endif
