#include "client.hpp"

#include "libplatform/platform.hpp"

#include "client_private.hpp"
#include "config.hpp"
#include "oauth1_data.hpp"

#include "libdiscogs/libdiscogs.hpp"
#include "liboauth1/oauth1.hpp"
#include "libplatform/file.hpp"
#include "libplatform/rapidjson_file.hpp"

#include <rapidjson/stream.h>
#include <rapidjson/stringbuffer.h>

#include "rapidjson_pretty.hpp"

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
		auto foo = m_rest->collection_folder_releases(m_username, platform::to_string_t(m_folder_id), page_id);

		try {
			foo.wait();
		}
		catch (web::http::http_exception &e){
			print_exception(e);
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

void client::folder_add()
{
	auto result = m_rest->collection_folder_add(m_username, m_cmd_arg);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	auto resp = discogs::unique(result.get());

	dcout << STR("Created folder") << dendl;
	dcout << STR("ID:   ") << resp->id << dendl;
	dcout << STR("Name: ") << resp->name << dendl;
	dcout << STR("URL:  ") << resp->resource_url << dendl;
}

void client::folder_get_meta()
{
	auto result = m_rest->collection_folder(m_username, m_folder_id);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	auto resp = discogs::unique(result.get());

	dcout << STR("Created folder") << dendl;
	dcout << STR("ID:   ") << resp->id << dendl;
	dcout << STR("Name: ") << resp->name << dendl;
	dcout << STR("URL:  ") << resp->resource_url << dendl;
}

void client::folder_delete()
{
	auto result = m_rest->collection_folder_delete(m_username, m_folder_id);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	dcout << STR("deleted folder ") << m_folder_id << dendl;
}

void client::folder_release()
{
	auto result = m_rest->collection_releases(m_username, m_release_id);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	auto ptr = discogs::unique(result.get());

	for(const auto &r : ptr->releases){
		dcout << STR("Folder ID: ") << r.folder_id << dendl;
		dcout << STR("Title:     ") << r.basic_information_.title << dendl;
	}
}

void client::collections_list()
{
	auto result = m_rest->collection_folders(m_username);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	auto c = discogs::unique(result.get());

	for(const auto &col : c->folders){
		dcout << col.name << dendl;
		dcout << STR("\tcount: ") << col.count << dendl;
		dcout << STR("\tid: ") << col.id << dendl;
	}
}

void client::collection_add()
{
	auto result = m_rest->collection_add_to_folder(
		m_username, m_folder_id, m_release_id);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	auto c = discogs::unique(result.get());

	dcout << STR("Added to collection") << dendl;
	dcout << STR("instance_id : ") << c->instance_id << dendl;
	dcout << STR("resource_url: ") << c->resource_url << dendl;
}

void client::collection_upd()
{
	auto result = m_rest->collection_change_rating_of_release(
		m_username,
		m_folder_id,
		m_release_id,
		m_instance_id,
		m_rating
	);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	dcout << STR("Collection updated") << dendl;
}

void client::collection_del()
{
	auto result = m_rest->collection_delete_instance_from_folder(
		m_username,
		m_folder_id,
		m_release_id,
		m_instance_id
	);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	dcout << STR("Release ") << m_release_id << STR(" deleted from folder ") << m_folder_id << dendl;
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
}

void client::market_get()
{
	auto result =
		m_rest->market_get(m_username);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
	}

	auto market_get = discogs::unique(result.get());

	for(const auto &l : market_get->listings){
		dcout << l.release.artist << STR(" - ") << l.release.title << dendl;
		dcout << STR("  URL      : ") << l.uri << dendl;
		dcout << STR("  In cart? : ") << (l.in_cart ? STR("Yes") : STR("No")) << dendl;
		dcout << STR("  Price    : ") << l.original_price_.value << STR(' ') << l.original_price_.curr_abbr << dendl;
		dcout << STR("  Price    : ") << l.original_price_.converted.value << STR(' ') << l.original_price_.converted.curr_abbr << dendl;
		dcout << dendl;
	}
}

void client::market_listing()
{
	const int arg = std::stoi(m_cmd_arg);

	auto result =
		m_rest->market_listing(arg);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
	}

	auto l = discogs::unique(result.get());

	dcout << l->release.artist << STR(" - ") << l->release.title << dendl;
	dcout << STR("  URL      : ") << l->uri << dendl;
	dcout << STR("  In cart? : ") << (l->in_cart ? STR("Yes") : STR("No")) << dendl;
	dcout << STR("  Price    : ") << l->original_price_.value << STR(' ') << l->original_price_.curr_abbr << dendl;
	dcout << STR("  Price    : ") << l->original_price_.converted.value << STR(' ') << l->original_price_.converted.curr_abbr << dendl;
	dcout << dendl;
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

void client::master_print()
{
	int master_id = std::stoi(m_cmd_arg);
	auto result = m_rest->master(master_id);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
	}

	auto m = discogs::unique(result.get());

	bool first = true;
	dcout << STR("Printing Master ") << m->id << dendl << dendl;
	for(const auto &a: m->artists){
		dcout << STR("Artist: ") << a.name << dendl;
	}
	dcout << STR("Title:  ") << m->title << dendl;
	dcout << STR("Year:   ") << m->year << dendl;
	dcout << STR("Genres: ");
	for(const auto &g: m->genres){
		if(!first){
			dcout << STR(", ");
		}
		first = false;
		dcout << g;
	}
	dcout << dendl;

	dcout << STR("Styles: ");
	first = true;
	for (const auto &s : m->styles) {
		if (!first) {
			dcout << STR(", ");
		}
		first = false;
		dcout << s;
	}
	dcout << dendl;

	dcout << STR("Titles:") << dendl;
	for(const auto &t : m->tracklist){
		dcout << STR("  ") << t.position
			<< STR(" - ") << t.title;
		if (t.duration.length() > 0) {
			dcout << STR(" [") << t.duration << STR(']');
		}
		dcout << dendl;
	}
}

void client::search()
{
	std::vector<std::pair<platform::string_t, platform::string_t>> args;

	args.emplace_back(STR("artist"), STR("Chicane"));

	auto result = m_rest->search(args);

	try {
		result.wait();
	}
	catch (web::http::http_exception &e) {
		print_exception(e);
	}

	auto search = discogs::unique(result.get());

	for(const auto &r : search->results){
		dcout << r.title << dendl;
	}
}

void client::identify()
{
	auto result = m_rest->identity();

	try {
		result.wait();
	}
	catch (const web::http::http_exception &) {
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
	if(
		data.consumer_key.length() == 0 ||
		data.consumer_secret.length() == 0)
	{
		dcout << STR("OAuth is not configured.  Please add your consumer key and secret to oauth1_data.cpp") << dendl;
		return;
	}

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
	auto result = m_rest->download_url(m_cmd_arg);

	try {
		result.wait();
	}
	catch(const web::http::http_exception &e) {
		print_exception(e);
		return;
	}

	const platform::char_t *fname = STR("download.json");

	platform::file file;
	bool rc = file.open(fname,
		platform::file::io_mode::write,
		platform::file::create_mode::trunc );
	if(!rc){
		dcout << STR("ERROR: Failed to open ") << fname;
		return;
	}

	const platform::string_t json_data = result.get();

	// This will take the json we get from the website and run
	// it through the rapidjson parser, and write it out again
	// but with pretty formatting, so it's easier to read.

	// File output routine.
	char buf[1024];
	platform::PlatformWriteStream pws{ file, buf, sizeof(buf) };
	platform::PrettyFileWriter pfw{ pws };
	pfw.SetIndent('\t', 1);

	// String stream that will read the document.
	rapidjson::GenericStringStream<rjs_UTF_t> input{ json_data.c_str() };

	// The JSON parser object, will forward the input to the PrettyFileWriter.
	rapid_pretty_parser<platform::PrettyFileWriter> pw{ pfw };

	rapidjson::GenericReader<rjs_UTF_t, rjs_UTF_t> r;
	rapidjson::ParseResult pr = r.Parse(input, pw);

	if(pr.IsError()){
		dcout << STR("JSON parse and reformat failed, writing out as unformatted");
		file.truncate();
		file.write_utf8(json_data);
		return;
	}

	const auto sz = file.length();

	dcout << STR("Written ") << sz << STR(" bytes to ") << fname << dendl;
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

	case ParserCommand::folder_add:
		folder_add();
		break;

	case ParserCommand::folder_get_meta:
		folder_get_meta();
		break;

	case ParserCommand::folder_delete:
		folder_delete();
		break;

	case ParserCommand::folder_release:
		folder_release();
		break;

	case ParserCommand::collection:
		collections_list();
		break;

	case ParserCommand::collection_add:
		collection_add();
		break;

	case ParserCommand::collection_upd:
		collection_upd();
		break;

	case ParserCommand::collection_del:
		collection_del();
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

	case ParserCommand::master_print:
		master_print();
		break;

	case ParserCommand::market_get:
		market_get();
		break;

	case ParserCommand::market_listing:
		market_listing();
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


