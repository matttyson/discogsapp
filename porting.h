#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <cstring>


namespace discogs {

#ifdef DISCOGS_WCHAR
typedef std::wstring string_t;
typedef wchar_t char_t;
#define dcout std::wcout
#define dcerr std::wcerr
#define dendl L"\r\n"
typedef std::wofstream dofstream;
typedef std::wifstream difstream;
#define STR(x) L ## x

template <typename T>
static string_t
to_string_t(T x)
{
	return std::to_wstring(x);
}

std::wstring
to_string_t(const std::string &str);

std::wstring
to_string_t(const char * str);

static int strcmp(const char_t *str1, const char_t *str2)
{
	return ::wcscmp(str1, str2);
}

#else
typedef std::string string_t;
typedef char char_t;
#define dcout std::cout
#define dcerr std::cerr
typedef std::ofstream dofstream;
typedef std::ifstream difstream;
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

static
std::string to_string_t(const char *str)
{
	return std::string(str);
}

static int strcmp(const char_t *str1, const char_t *str2)
{
	return ::strcmp(str1, str2);
}

#endif

}
