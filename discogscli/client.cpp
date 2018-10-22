#include "client.hpp"

#include "porting.h"
#include "libdiscogs/libdiscogs.hpp"
#include "client_private.hpp"

#include <iostream>
#include <string>

void print_exception(const web::http::http_exception &e)
{
	dcout << STR("HTTP Error (");
	dcout << e.error_code();
	dcout << STR(") ");
	dcout << discogs::to_string_t(e.what());
	dcout << dendl;
}

client::client(const discogs::string_t &user_agent)
	:m_command(ParserCommand::NO_COMMAND),
	m_rest(std::make_unique<discogs::rest>(user_agent)),
	m_release_id(-1), m_rating(-1)
{
	// TODO - Make the config load from a json file and
	// not in the object constructor.
	discogs::difstream file;
	file.open("apikey", std::ios::in);
	if(file.is_open()){
		discogs::string_t key;
		getline(file, key);
		m_rest->set_session_key(key);
	}
	m_rest->set_per_page(100);
}


client::~client()
{
}

void client::test_parse()
{
	/*
	FILE *fp = fopen("D:\\Programming\\projects\\discogsrest\\support\\label.json", "rb");
	char buffer[2028];
	rapidjson::Reader reader;
	rapidjson::FileReadStream frs(fp, buffer, sizeof(buffer));
	label_parser parser;
	reader.Parse(frs, parser);

	fclose(fp);
	*/
}

static bool has_more_pages(const discogs::parser::paginate::pagination &p)
{
	return p.page < p.pages;
}


void client::folder_list()
{
	std::vector<discogs::parser::folder_release::release> releases;

	bool keep_going = false;
	int page_id = 1;

	do {
		auto foo = m_rest->folder_releases(m_username, m_folder_id, page_id);

		try {
			foo.wait();
		}
		catch (web::http::http_exception &e){
			print_exception(e);
			return;
		}
		catch (std::exception &e) {
			return;
		}

		auto c = foo.get();

		releases.insert(releases.end(),
			std::make_move_iterator(c.release_.begin()),
			std::make_move_iterator(c.release_.end()));

		keep_going = has_more_pages(c.pages);

		dcerr << STR("Downloaded page ") << page_id << dendl;
		page_id++;

	} while (keep_going);

	std::sort(releases.begin(), releases.end(), [](
			const discogs::parser::folder_release::release &lhs,
			const discogs::parser::folder_release::release &rhs) -> bool
	{
		return lhs.basic_information_.title < rhs.basic_information_.title;
	});

	for (const auto &e : releases) {
		const auto &bi = e.basic_information_;
		if(bi.artists.size() > 0){
			dcout << bi.artists[0].name << STR(" - ");
		}

		dcout << bi.title;

		if(bi.formats.size() > 0){
			dcout << STR(" [");
			bool first = true;
			for (const auto &fmt : bi.formats) {
				if(!first){
					dcout << STR(", ");
				}
				first = false;
				dcout << fmt.name;

				for(const auto &desc : fmt.descriptions){
					if(!first){
						dcout << STR(", ");
					}
					dcout << desc;
				}
			}
			dcout << STR("]\n");
		}
	}
}

void client::collections_list()
{
	auto result = m_rest->collection(m_username);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}
	catch(std::exception &e){
		return;
	}

	auto c = result.get();

//	std::sort(c.labels_.begin(), c.labels_.end(),[](collection::)

	for(const auto &col : c.folders){
		dcout << col.name << dendl;
		dcout << STR("\tcount: ") << col.count << dendl;
		dcout << STR("\tid: ") << col.id << dendl;
	}
}

void client::wantlist_list()
{
	int page_id = 1;
	bool keep_going = false;

	std::vector<discogs::parser::common::want> want_list;

	do {
		auto result = m_rest->wantlist(m_username, page_id);

		try {
			result.wait();
		}
		catch (web::http::http_exception &e) {
			print_exception(e);
			return;
		}
		catch (std::exception &e){
			return;
		}

		auto c = result.get();

		//keep_going = has_more_pages(c.pages);

		want_list.insert(want_list.end(),
			std::make_move_iterator(c.want_.begin()),
			std::make_move_iterator(c.want_.end())
		);
		page_id++;
	} while (keep_going);

	std::sort(want_list.begin(), want_list.end(),[](
		const discogs::parser::common::want &lhs,
		const discogs::parser::common::want &rhs) -> bool
	{
		return lhs.basic_information_.title < rhs.basic_information_.title;
	}
	);
	dcout << STR("Dumping data") << dendl;
	for(const auto &w : want_list){
		dcout << w.basic_information_.title << dendl;
	}
}

void client::wantlist_delete()
{
	auto result =
	m_rest->delete_wantlist(m_release_id, m_username);

	try {
		result.wait();
		dcout << STR("Deleted release ") << m_release_id << dendl;
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}
	catch(std::exception &e){
		return;
	}
}

void client::wantlist_add()
{
	auto result =
		m_rest->add_wantlist(m_release_id, m_username);

	try {
		result.wait();
		dcout << STR("Added release ") << m_release_id << dendl;
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}
	catch(std::exception &e){
		return;
	}
}

void client::wantlist_update()
{
	auto result =
		m_rest->update_wantlist(m_release_id, m_username, m_notes, m_rating);

	try {
		result.wait();
		dcout << STR("Updated release ") << m_release_id << dendl;
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}
	catch(std::exception &e){
		return;
	}
}

void client::release_print()
{
	auto result =
		m_rest->release(m_release_id);

	try {
		result.wait();
	}
	catch(web::http::http_exception &e) {
		print_exception(e);
	}

	auto release = result.get();
	bool start = true;

	dcout << STR("Printing Release ") << release.id << dendl << dendl;
	for (const auto &a : release.artists) {
		dcout << STR("Artist: ") << a.name << dendl;
	}
	dcout << STR("Title : ") << release.title << dendl;
	dcout << STR("Year  : ") << release.year << dendl;
	for(const auto &f : release.formats){
		dcout << STR("Format: ") << f.name;
		for(const auto &d : f.descriptions){
			dcout << STR(", ") << d;
		}
	}
	dcout << dendl;
	dcout << STR("Genres: ");
	for (const auto &g : release.genres) {
		if (!start) {
			dcout << STR(", ");
		}
		start = false;
		dcout << g;
	}
	dcout << dendl;
	dcout << STR("URL   : ") << release.master_url << dendl;
	dcout << STR("Tracks: ") << dendl;
	for(const auto &t: release.tracklist){
		dcout << STR("  ") << t.position
			<< STR(" - ") << t.title
			<< STR(" [") << t.duration << STR(']') << dendl;
	}
}

int client::run(int argc, discogs::char_t *argv[])
{
	if (process_args(argc, argv) != 0) {
		return -1;
	}

	switch(m_command){
	case ParserCommand::folder_list:
		folder_list();
		break;

	case ParserCommand::collection:
		collections_list();
		break;

	case ParserCommand::wantlist:
		wantlist_list();
		break;

	case ParserCommand::wantlist_del:
		wantlist_delete();
		break;

	case ParserCommand::wantlist_add:
		wantlist_add();
		break;

	case ParserCommand::wantlist_upd:
		wantlist_update();
		break;

	case ParserCommand::release_print:
		release_print();
		break;

	case ParserCommand::NO_COMMAND:
	default:
		break;
	}

	return 0;
}


