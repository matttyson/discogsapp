#pragma once

#include "porting.h"
#include <memory>

namespace discogs {

class config_private;

class config {
public:
	config(const discogs::string_t &filename);
	~config();

	bool read();
	bool write();

	bool get(const discogs::string_t &key, discogs::string_t &value);
	bool get(const discogs::string_t &key, int &value);

	void set(const discogs::string_t &key, const discogs::string_t &value);
	void set(const discogs::string_t &key, int value);

	void remove(const discogs::string_t &key);

private:
	std::unique_ptr<config_private> m_data;
};

}
