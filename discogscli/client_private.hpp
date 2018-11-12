#pragma once

enum class ParserCommand {
	collection,
	collection_add,
	collection_upd,
	folder_list,
	folder_add,
	folder_get_meta,
	folder_delete,
	folder_release,
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
