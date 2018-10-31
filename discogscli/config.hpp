#pragma once

#include "libplatform/platform.hpp"

#include <memory>

namespace discogs {

class config_private;

class config {
public:
	config(const platform::string_t &filename);
	~config();

	bool read();
	bool write();

	bool get(const platform::string_t &key, platform::string_t &value);
	bool get(const platform::string_t &key, int &value);

	void set(const platform::string_t &key, const platform::string_t &value);
	void set(const platform::string_t &key, int value);

	void remove(const platform::string_t &key);

private:
	std::unique_ptr<config_private> m_data;
};

}
