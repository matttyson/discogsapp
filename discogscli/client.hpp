#pragma once

#include "porting.h"
#include "config.hpp"
#include <memory>

namespace discogs {
	class rest;
}

enum class ParserCommand;

class client
{
public:
	client(const discogs::string_t &user_agent);
	~client();

	int run(int argc, discogs::char_t *argv[]);

private:
	int process_args(int argc, discogs::char_t *argv[]);
	void folder_list();
	void collections_list();

	void test_parse();

	void release_print();

	void wantlist_list();
	void wantlist_delete();
	void wantlist_add();
	void wantlist_update();

	void identify();

	void authenticate();

	void apply_config();

private:
	ParserCommand m_command;
	std::unique_ptr<discogs::rest> m_rest;
	
	// Arguments
	int m_release_id;
	int m_rating;

	discogs::config m_cfg;

	discogs::string_t m_username;
	discogs::string_t m_folder_id;
	discogs::string_t m_notes;
};

