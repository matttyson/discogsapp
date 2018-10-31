#include "client.hpp"

#include "libplatform/platform.hpp"

#include "client_private.hpp"
#include "config.hpp"
#include "oauth1_data.hpp"

#include "libdiscogs/libdiscogs.hpp"
#include "liboauth1/oauth1.hpp"

#include <iostream>
#include <string>

void open_browser(const platform::string_t &str);

void print_exception(const web::http::http_exception &e)
{
	dcout << STR("HTTP Error (");
	dcout << e.error_code();
	dcout << STR(") ");
	dcout << platform::to_string_t(e.what());
	dcout << dendl;
}

client::client(const platform::string_t &user_agent)
	:m_command(ParserCommand::NO_COMMAND),
	m_rest(std::make_unique<discogs::rest>(user_agent)),
	m_release_id(-1), m_rating(-1),
	m_cfg(STR("discogscli.json"))
{
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
	std::vector<discogs::parser::folder_release_item> releases;

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

		auto c = discogs::unique(foo.get());

		releases.insert(releases.end(),
			std::make_move_iterator(c->release_.begin()),
			std::make_move_iterator(c->release_.end()));

		keep_going = has_more_pages(c->pages);

		dcerr << STR("Downloaded page ") << page_id << dendl;
		page_id++;

	} while (keep_going);

	std::sort(releases.begin(), releases.end(), [](
			const discogs::parser::folder_release_item &lhs,
			const discogs::parser::folder_release_item &rhs) -> bool
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

	auto c = discogs::unique(result.get());

	for(const auto &col : c->folders){
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

		auto c = discogs::unique(result.get());

		keep_going = has_more_pages(c->pages);

		want_list.insert(want_list.end(),
			std::make_move_iterator(c->want_.begin()),
			std::make_move_iterator(c->want_.end())
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
	m_rest->wantlist_delete(m_release_id, m_username);

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
		m_rest->wantlist_add(m_release_id, m_username);

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
		m_rest->wantlist_update(m_release_id, m_username, m_notes, m_rating);

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

	auto release = discogs::unique(result.get());
	bool start = true;

	dcout << STR("Printing Release ") << release->id << dendl << dendl;
	for (const auto &a : release->artists) {
		dcout << STR("Artist: ") << a.name << dendl;
	}
	dcout << STR("Title : ") << release->title << dendl;
	dcout << STR("Year  : ") << release->year << dendl;
	for(const auto &f : release->formats){
		dcout << STR("Format: ") << f.name;
		for(const auto &d : f.descriptions){
			dcout << STR(", ") << d;
		}
	}
	dcout << dendl;
	dcout << STR("Genres: ");
	for (const auto &g : release->genres) {
		if (!start) {
			dcout << STR(", ");
		}
		start = false;
		dcout << g;
	}
	dcout << dendl;
	dcout << STR("URL   : ") << release->master_url << dendl;
	dcout << STR("Tracks: ") << dendl;
	for(const auto &t: release->tracklist){
		dcout << STR("  ") << t.position
			<< STR(" - ") << t.title;
		if(t.duration.length() > 0){
			dcout << STR(" [") << t.duration << STR(']');
		}
		dcout << dendl;
	}
}

void client::identify()
{
	auto result = m_rest->identity();

	try {
		result.wait();
	}
	catch (const web::http::http_exception &e) {
		dcout << STR("You are not logged in") << dendl;
		return;
	}

	auto id = discogs::unique(result.get());

	dcout << STR("Logged in as:") << dendl << dendl;
	dcout << STR("Username: ") << id->username << dendl;
	dcout << STR("ID      : ") << id->id << dendl;
	dcout << STR("URL     : ") << id->resource_url << dendl;
}

void client::login()
{
	const discogs::oauth1_data data = get_oauth_data();

	discogs::oauth1 auth(data, open_browser);

	auto task = auth.authenticate();

	if(task.get()){
		dcout << STR("Authenticated successfully") << dendl;

		m_cfg.set(STR("user_access_token"), auth.access_token());
		m_cfg.set(STR("user_secret"), auth.secret());
		m_cfg.write();
	}
	else {
		// Authentication failed.
		dcout << STR("Authentication failed") << dendl;
	}
}

void client::logout()
{
	m_cfg.remove(STR("user_access_token"));
	m_cfg.remove(STR("user_secret"));
	m_cfg.write();
}

void client::download()
{
	// TODO:  The output here will be whatever json
	// the endpoint gives us, which will usally be
	// one long string with no line breaks.
	// I should use RapidJSON to format this
	// so that it's written out in a pretty way.

	auto result = m_rest->download_url(m_cmd_arg);

	try {
		result.wait();
	}
	catch(const web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	platform::string_t filename = STR("download.json");

	platform::dofstream file;
	file.open(filename);

	if(!file.is_open()){
		dcout << STR("Error opening file") << dendl;
		return;
	}

	file << result.get();

	dcout << STR("Written output to ") << filename << dendl;

}

void client::apply_config()
{
	const discogs::oauth1_data data = get_oauth_data();

	if(!m_cfg.read()){
		return;
	}

	platform::string_t user_access_token;
	platform::string_t user_secret;

	if(!m_cfg.get(STR("user_access_token"), user_access_token)){
		return;
	}

	if (!m_cfg.get(STR("user_secret"), user_secret)) {
		return;
	}

	m_rest->oauth_configure(data, user_access_token, user_secret);
}

int client::run(int argc, platform::char_t *argv[])
{
	if (process_args(argc, argv) != 0) {
		return -1;
	}

	apply_config();

	switch(m_command){
	case ParserCommand::login:
		login();
		break;

	case ParserCommand::logout:
		logout();
		break;

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

	case ParserCommand::identify:
		identify();
		break;

	case ParserCommand::download:
		download();
		break;

	case ParserCommand::NO_COMMAND:
	default:
		break;
	}

	return 0;
}


