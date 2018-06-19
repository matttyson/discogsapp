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

private:
	ParserCommand m_command;
	std::unique_ptr<discogs::rest> m_rest;
	
	// Arguments
	discogs::string_t m_username;
	discogs::string_t m_folder_id;
};

