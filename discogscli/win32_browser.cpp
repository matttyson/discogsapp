#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>

#include "libplatform/platform.hpp"

void open_browser(const platform::string_t &str)
{
	HINSTANCE inst = ShellExecute(NULL, STR("open"), str.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
