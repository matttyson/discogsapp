/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"

namespace discogs {
namespace parser {

class identity {
public:
	identity():id(0){}
	~identity(){}
	identity(const identity &rhs) = default;
	identity(identity &&rhs) noexcept = default;
	identity& operator=(const identity &rhs) = default;
	identity& operator=(identity &&rhs) noexcept = default;

	int id;
	string_t username;
	string_t resource_url;
	string_t consumer_name;
	string_t message;
};

} // namespace discogs
} // namespace parser
