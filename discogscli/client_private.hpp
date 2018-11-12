#pragma once

enum class ParserCommand {
	collection,
	collection_add,
	collection_upd,
	collection_del,
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
	master_print,
	login,
	logout,
	identify,
	download,
	NO_COMMAND
};
