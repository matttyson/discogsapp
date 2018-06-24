#pragma once

#include "porting.h"
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
	void list_folder();
	void list_collections();
	void list_wantlist();
	void test_parse();
	void delete_wantlist();
	void add_wantlist();
	void update_wantlist();

private:
	ParserCommand m_command;
	std::unique_ptr<discogs::rest> m_rest;
	
	// Arguments
	int m_release_id;
	int m_rating;

	discogs::string_t m_username;
	discogs::string_t m_folder_id;
	discogs::string_t m_notes;
};

