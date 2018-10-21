/* clang-format off */
#pragma once

#include <vector>
#include <string>
#include <memory>

#ifdef DISCOGS_WCHAR
typedef std::wstring string_t;
typedef wchar_t char_t;
#else
typedef std::string string_t;
typedef char char_t;
#endif
