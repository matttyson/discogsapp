#include "client.hpp"

#include "libdiscogs/libdiscogs.hpp"
#include "client_private.hpp"


client::client(const discogs::string_t &user_agent)
	:m_command(ParserCommand::NO_COMMAND),
	m_rest(std::make_unique<discogs::rest>(user_agent))
{
	// TODO - read this in from a config file
	m_rest->set_session_key(STR(""));
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


void client::list_folder()
{
	std::vector<discogs::parser::folder_releases::release> releases;

	bool keep_going = false;
	int page_id = 1;

	do {
		auto foo = m_rest->folder_releases(m_username, m_folder_id, page_id);

		try {
			foo.wait();
		}
		catch (std::exception &e) {
			std::cerr << e.what() << "\n";
			return;
		}

		auto c = foo.get();

		releases.reserve(releases.capacity() + c.release_.size());
		releases.insert(releases.end(),
			std::make_move_iterator(c.release_.begin()),
			std::make_move_iterator(c.release_.end()));

		keep_going = has_more_pages(c.pages);

		dcerr << STR("Downloaded page ") << page_id << dendl;
		page_id++;

	} while (keep_going);

	std::sort(releases.begin(), releases.end(), [](
			const discogs::parser::folder_releases::release &lhs,
			const discogs::parser::folder_releases::release &rhs) -> bool
	{
		return lhs.basic_information_.title < rhs.basic_information_.title;
	});

	for (const auto &e : releases) {
		const auto &bi = e.basic_information_;
		dcout << bi.title << dendl;
	}
}

void client::list_collections()
{
	auto result = m_rest->collection(m_username);

	try {
		result.wait();
	}
	catch(std::exception &e){
		std::cerr << e.what() << "\n";
		return;
	}

	auto c = result.get();

//	std::sort(c.labels_.begin(), c.labels_.end(),[](collection::)

	for(const auto &col : c.folders_){
		dcout << col.name << dendl;
		dcout << STR("\tcount: ") << col.count << dendl;
		dcout << STR("\tid: ") << col.id << dendl dendl;
	}
}

void client::list_wantlist()
{
	int page_id = 1;
	bool keep_going = false;

	std::vector<discogs::parser::wantlist::want> want_list;

	do {
		auto result = m_rest->wantlist(m_username, page_id);

		try {
			result.wait();
		}
		catch (std::exception &e){
			std::cerr << e.what() << "\n";
			return;
		}

		auto c = result.get();

		//keep_going = has_more_pages(c.pages);

		want_list.insert(want_list.end(),
			std::make_move_iterator(c.wants_.begin()),
			std::make_move_iterator(c.wants_.end())
		);
		page_id++;
	} while (keep_going);

	std::sort(want_list.begin(), want_list.end(),[](
		const discogs::parser::wantlist::want &lhs,
		const discogs::parser::wantlist::want &rhs) -> bool
	{
		return lhs.basic_information_.title < rhs.basic_information_.title;
	}
	);
	dcout << STR("Dumping data") << dendl;
	for(const auto &w : want_list){
		dcout << w.basic_information_.title << dendl;
	}

}

void client::delete_wantlist()
{
	auto result =
	m_rest->delete_wantlist(m_release_id, m_username);

	try {
		result.wait();
		dcout << STR("Deleted release ") << m_release_id << dendl;
	}
	catch(std::exception &e){
		std::cout << e.what() << "\n";
	}
}

void client::add_wantlist()
{
	auto result =
		m_rest->add_wantlist(m_release_id, m_username);

	try {
		result.wait();
		dcout << STR("Added release ") << m_release_id << dendl;
	}
	catch(std::exception &e){
		std::cout << e.what() << "\n";
	}
}

void client::update_wantlist()
{
	auto result =
		m_rest->update_wantlist(m_release_id, m_username, m_notes, m_rating);

	try {
		result.wait();
		dcout << STR("Updated release ") << m_release_id << dendl;
	}
	catch(std::exception &e){
		std::cout << e.what() << "\n";
	}
}

int client::run(int argc, discogs::char_t *argv[])
{
	if (process_args(argc, argv) != 0) {
		return -1;
	}

	switch(m_command){
	case ParserCommand::list_folder:
		list_folder();
		break;

	case ParserCommand::collection:
		list_collections();
		break;

	case ParserCommand::wantlist:
		list_wantlist();
		break;

	case ParserCommand::wantlist_del:
		delete_wantlist();
		break;

	case ParserCommand::wantlist_add:
		add_wantlist();
		break;

	case ParserCommand::wantlist_upd:
		update_wantlist();
		break;

	case ParserCommand::NO_COMMAND:
	default:
		break;
	}

	return 0;
}


