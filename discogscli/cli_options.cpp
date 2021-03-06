#include "client.hpp"

#ifdef PLATFORM_WCHAR
#define CXXOPTS_WIDE_STRING
#endif

#include <cxxopts.hpp>

#include "libplatform/platform.hpp"
#include "client_private.hpp"


int client::process_args(int argc, platform::char_t *argv[])
{
	cxxopts::Options options(STR("discogs"), STR("Discogs CLI driver"));

	options.add_options(STR("Driver"))
		(STR("help"), STR("Print Help"), cxxopts::value<bool>())
		(STR("v,verbose"), STR("Verbose output"), cxxopts::value<bool>()->default_value(STR("false")))
		(STR("c,config"), STR("Config file to use"), cxxopts::value<cxxopts::String>())
		(STR("login"), STR("Authenticate with discogs via oauth (web browser required)"))
		(STR("logout"), STR("Clear authentication tokens"))
		;

	options.add_options(STR("Discogs"))
		(STR("whoami"), STR("Print out information about who you are authenticated as"))
		(STR("download"), STR("Download a URL from discogs"), cxxopts::value<cxxopts::String>())
		(STR("folder-list"), STR("List all the items in a folder, requires username, folder-id"))
		(STR("folder-add"), STR("Add a folder"), cxxopts::value<cxxopts::String>())
		(STR("folder-meta"), STR("Get folder metadata, requires username, folder-id"))
		(STR("folder-del"), STR("Delete a folder, requires username, folder-id"))
		(STR("folder-rel"), STR("Return a list of folders that contain the given release, requires release"))
		(STR("collections"), STR("List all the collections for a user, requires username"))
		(STR("collection-add"), STR("Add a release to a collection folder, requires username, folder-id, release-id"))
		(STR("collection-upd"), STR("Update a release in your collection, username, folder, release, instance"))
		(STR("collection-del"), STR("Delete an item from a collection, username, folder, released, instance"))
		(STR("wantlist"), STR("List the users wantlist, requires username"))
		(STR("wantlist-add"), STR("Add a release to the wantlist, requires username, release"))
		(STR("wantlist-del"), STR("Delete an item from the wantlist, requires username, release"))
		(STR("wantlist-upd"), STR("Update wantlist itemt, requires username, release [note, rating]"))
		(STR("release-print"), STR("Print out a release, requires release"))
		(STR("master-print"), STR("Print out a master"), cxxopts::value<cxxopts::String>())
		(STR("market-get"), STR("Get a users listed market items, requires username"))
		(STR("market-listing"), STR("Get information about one item on the market"), cxxopts::value<cxxopts::String>())
		;

	options.add_options(STR("Ancillary"))
		(STR("u,username"), STR("A username to query"), cxxopts::value<cxxopts::String>())
		(STR("f,folder-id"), STR("The ID of the folder to process"), cxxopts::value<int>())
		(STR("i,instance"), STR("The ID of the instance"), cxxopts::value<int>())
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

	if (r.count(STR("folder-add"))) {
		m_command = ParserCommand::folder_add;
		m_cmd_arg = r[STR("folder-add")].as<cxxopts::String>();
		command_count++;
	}

	if (r.count(STR("folder-meta"))) {
		m_command = ParserCommand::folder_get_meta;
		command_count++;
	}

	if (r.count(STR("folder-del"))) {
		m_command = ParserCommand::folder_delete;
		command_count++;
	}

	if (r.count(STR("folder-rel"))) {
		m_command = ParserCommand::folder_release;
		command_count++;
	}

	if(r.count(STR("collections"))){
		m_command = ParserCommand::collection;
		command_count++;
	}

	if(r.count(STR("collection-add"))){
		m_command = ParserCommand::collection_add;
		command_count++;
	}

	if (r.count(STR("collection-upd"))) {
		m_command = ParserCommand::collection_upd;
		command_count++;
	}

	if (r.count(STR("collection-del"))) {
		m_command = ParserCommand::collection_del;
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

	if(r.count(STR("master-print"))){
		m_command = ParserCommand::master_print;
		m_cmd_arg = r[STR("master-print")].as<cxxopts::String>();
		command_count++;
	}

	if(r.count(STR("whoami"))){
		m_command = ParserCommand::identify;
		command_count++;
	}

	if(r.count(STR("login"))){
		m_command = ParserCommand::login;
		command_count++;
	}

	if(r.count(STR("logout"))){
		m_command = ParserCommand::logout;
		command_count++;
	}

	if(r.count(STR("download"))){
		m_command = ParserCommand::download;
		m_cmd_arg = r[STR("download")].as<cxxopts::String>();
		command_count++;
	}

	if(r.count(STR("market-get"))){
		m_command = ParserCommand::market_get;
		command_count++;
	}

	if (r.count(STR("market-listing"))) {
		m_command = ParserCommand::market_listing;
		m_cmd_arg = r[STR("market-listing")].as<cxxopts::String>();
		command_count++;
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
		m_folder_id = r[STR("folder-id")].as<int>();
	}

	if (r.count(STR("instance"))) {
		m_instance_id = r[STR("instance")].as<int>();
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
