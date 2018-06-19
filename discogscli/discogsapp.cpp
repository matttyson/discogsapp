// discogsapp.cpp : Defines the entry point for the application.
//

#include "discogsapp.h"
#include "client.hpp"

using namespace std;

discogs::string_t global_user_agent(STR("madabbot test client/0.1"));

#ifdef DISCOGS_WCHAR
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
   
	discogs::char_t *dargv[] = {
		(discogs::char_t*)STR("foobar"),
		(discogs::char_t*)STR("--wantlist"),
		(discogs::char_t*)STR("-u"),
		(discogs::char_t*)STR("madabbot")
	};
	int count = sizeof(dargv) / sizeof(void*);
    

	client c(global_user_agent);
	return c.run(count, dargv);
	//return c.run(argc, argv);
}

