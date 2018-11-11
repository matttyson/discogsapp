
#include "libplatform/platform.hpp"
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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


const char *cmds[] = {
	"/usr/bin/xdg-open",
	"/usr/bin/gnome-open",
	"/usr/bin/kde-open",
	"/usr/bin/sensible-browser"
};

static bool find_command(const char *cmdpath)
{
	struct stat statbuf;
	int rc = stat(cmdpath, &statbuf);
	return rc == 0;
}

void open_browser(const platform::string_t &str)
{
	platform::char_t buffer[512];
	for(int i = 0; i < sizeof(cmds) / sizeof(void*); i++){
		if(find_command(cmds[i])){
			const int rc = snprintf(buffer,sizeof(buffer),"%s \"%s\"", cmds[i], str.c_str());
			if(rc == sizeof(buffer)){
				return;
			}
			(void)system(buffer);
			return;
		}
	}
}

