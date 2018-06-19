#include "client.hpp"

#ifdef DISCOGS_WCHAR
#define CXXOPTS_WIDE_STRING
#endif

#include <cxxopts.hpp>

#include "porting.h"
#include "client_private.hpp"


int client::process_args(int argc, discogs::char_t *argv[])
{
	cxxopts::Options options(STR("discogs"), STR("Discogs CLI driver"));

	options.add_options(STR("Driver"))
		(STR("help"), STR("Print Help"), cxxopts::value<bool>())
		(STR("v,verbose"), STR("Verbose output"), cxxopts::value<bool>()->default_value(STR("false")))
		(STR("c,config"), STR("Config file to use"), cxxopts::value<cxxopts::String>())
		;

	options.add_options(STR("Discogs"))
		(STR("list-folder"), STR("List all the items in a folder, requires username, folder-id"))
		(STR("collections"), STR("List all the collections for a user, requires username"))
		(STR("wantlist"), STR("List the users wantlist, requires username"))
		;

	options.add_options(STR("Ancillary"))
		(STR("u,username"), STR("A username to query"), cxxopts::value<cxxopts::String>())
		(STR("f,folder-id"), STR("The ID of the folder to process"), cxxopts::value<cxxopts::String>())
		;

	cxxopts::ParseResult r = options.parse(argc, argv);

	const auto sz = r.arguments().size();

	if (r.count(STR("help")) > 0 || sz == 0) {
		dcout << options.help({ STR("Driver"),STR("Discogs"),STR("Ancillary") });
		return -1;
	}
	// Grab program commands
	if (r.count(STR("list-folder"))) {
		m_command = ParserCommand::list_folder;
	}

	if(r.count(STR("collections"))){
		m_command = ParserCommand::collection;
	}

	if(r.count(STR("wantlist"))){
		m_command = ParserCommand::wantlist;
	}

	// Grab ancillary arguments
	if (r.count(STR("username"))) {
		m_username = r[STR("username")].as<cxxopts::String>();
	}

	if (r.count(STR("folder-id"))) {
		m_folder_id = r[STR("folder-id")].as<cxxopts::String>();
	}



	return 0;
}
