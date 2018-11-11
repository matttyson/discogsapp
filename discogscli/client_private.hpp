#pragma once

enum class ParserCommand {
	collection,
	folder_list,
	folder_add,
	folder_get_meta,
	wantlist,
	wantlist_del,
	wantlist_add,
	wantlist_upd,
	release_print,
	login,
	logout,
	identify,
	download,
	NO_COMMAND
};

