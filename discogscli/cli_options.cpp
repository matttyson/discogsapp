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
		(STR("auth"), STR("Authenticate with discogs via oauth (web browser required)"))
		;

	options.add_options(STR("Discogs"))
		(STR("folder-list"), STR("List all the items in a folder, requires username, folder-id"))
		(STR("collections"), STR("List all the collections for a user, requires username"))
		(STR("wantlist"), STR("List the users wantlist, requires username"))
		(STR("wantlist-add"), STR("Add a release to the wantlist, requires username, release"))
		(STR("wantlist-del"), STR("Delete an item from the wantlist, requires username, release"))
		(STR("wantlist-upd"), STR("Update wantlist itemt, requires username, release [note, rating]"))
		(STR("release-print"), STR("Print out a release, requires release"))
		;

	options.add_options(STR("Ancillary"))
		(STR("u,username"), STR("A username to query"), cxxopts::value<cxxopts::String>())
		(STR("f,folder-id"), STR("The ID of the folder to process"), cxxopts::value<cxxopts::String>())
		(STR("r,release"), STR("Release ID"), cxxopts::value<int>())
		(STR("n,note"), STR("Notes"), cxxopts::value<cxxopts::String>())
		(STR("a,rating"), STR("Rating number"), cxxopts::value<int>())
		;

	cxxopts::ParseResult r = options.parse(argc, argv);

	const auto sz = r.arguments().size();
	int command_count = 0;

	if (r.count(STR("help")) > 0 || sz == 0) {
		dcout << options.help({ STR("Driver"),STR("Discogs"),STR("Ancillary") });
		return -1;
	}
	// Grab program commands
	if (r.count(STR("folder-list"))) {
		m_command = ParserCommand::folder_list;
		command_count++;
	}

	if(r.count(STR("collections"))){
		m_command = ParserCommand::collection;
		command_count++;
	}

	if(r.count(STR("wantlist"))){
		m_command = ParserCommand::wantlist;
		command_count++;
	}

	if(r.count(STR("wantlist-del"))){
		m_command = ParserCommand::wantlist_del;
		command_count++;
	}

	if(r.count(STR("wantlist-add"))){
		m_command = ParserCommand::wantlist_add;
		command_count++;
	}

	if(r.count(STR("wantlist-upd"))){
		m_command = ParserCommand::wantlist_upd;
		command_count++;
	}

	if(r.count(STR("release-print"))){
		m_command = ParserCommand::release_print;
		command_count++;
	}

	if(r.count(STR("auth"))){
		m_command = ParserCommand::authenticate;
	}

	if(command_count != 1){
		dcout << STR("Error: a single Discogs option must be selected") << dendl << dendl;
		dcout << options.help({ STR("Driver"),STR("Discogs"),STR("Ancillary") });
		return -1;
	}

	// Grab ancillary arguments
	if (r.count(STR("username"))) {
		m_username = r[STR("username")].as<cxxopts::String>();
	}

	if (r.count(STR("folder-id"))) {
		m_folder_id = r[STR("folder-id")].as<cxxopts::String>();
	}

	if (r.count(STR("release"))) {
		m_release_id = r[STR("release")].as<int>();
	}

	if (r.count(STR("note"))) {
		m_notes = r[STR("note")].as<cxxopts::String>();
	}

	if (r.count(STR("rating"))) {
		m_rating = r[STR("rating")].as<int>();
	}

	return 0;
}
