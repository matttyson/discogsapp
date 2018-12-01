#pragma once

#include "libplatform/platform.hpp"
#include "config.hpp"
#include <memory>

namespace discogs {
	class rest;
}

enum class ParserCommand;

class client
{
public:
	client(const platform::string_t &user_agent);
	~client();

	int run(int argc, platform::char_t *argv[]);

private:
	int process_args(int argc, platform::char_t *argv[]);
	void folder_list();
	void folder_add();
	void folder_get_meta();
	void folder_delete();
	void folder_release();

	void collections_list();
	void collection_add();
	void collection_upd();
	void collection_del();

	void test_parse();

	void release_print();
	void master_print();

	void search();

	void wantlist_list();
	void wantlist_delete();
	void wantlist_add();
	void wantlist_update();

	void market_get();
	void market_listing();

	void identify();

	void login();
	void logout();

	void download();

	void apply_config();

private:
	ParserCommand m_command;
	std::unique_ptr<discogs::rest> m_rest;
	
	// Arguments
	int m_release_id;
	int m_rating;
	int m_folder_id;
	int m_instance_id;

	discogs::config m_cfg;

	platform::string_t m_username;
	platform::string_t m_notes;
	platform::string_t m_cmd_arg;
};

