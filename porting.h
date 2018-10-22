#pragma once

#include <string>
#include <iostream>
#include <type_traits>


namespace discogs {

#ifdef DISCOGS_WCHAR
typedef std::wstring string_t;
typedef wchar_t char_t;
#define dcout std::wcout
#define dcerr std::wcerr
#define dendl L"\r\n"
#define dofstream std::wofstream
#define difstream std::wifstream
#define STR(x) L ## x

template <typename T>
static string_t
to_string_t(T x)
{
	return std::to_wstring(x);
}

#else
typedef std::string string_t;
typedef char char_t;
#define dcout std::cout
#define dcerr std::cerr
#define dofstream std::ofstream
#define difstream std::ifstream
#define dendl '\n'
#define STR(x) x

template <typename T>
static string_t
to_string_t(T x)
{
	return std::to_string(x);
}

static
std::string to_string(string_t str)
{
	return str;
}

#endif

}
