#include "client.hpp"

discogs::string_t global_user_agent(STR("madabbot test client/0.1"));

#ifdef DISCOGS_WCHAR
int wmain(int argc, wchar_t *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	client c(global_user_agent);

	return c.run(argc, argv);
}

