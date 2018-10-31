
#include "libplatform/platform.hpp"
#include <cstdlib>

/*
Linux being linux, there's a few ways to do this

xdg-open
gnome-open
kde-open
sensible-browser
python -m webbrowser "http://whatever"

We should probably work our way through the list of apps and see what exists
on the local system so we know which one to call

*/

void open_browser(const platform::string_t &str)
{
	platform::string_t browser_cmd(STR("xdg-open \"") + str + STR("\""));
	(void)system(browser_cmd.c_str());
}
