/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"

namespace discogs {
namespace parser {

class collection_add_response {
public:
	collection_add_response():instance_id(0){}
	~collection_add_response(){}
	collection_add_response(const collection_add_response &rhs) = default;
	collection_add_response(collection_add_response &&rhs) noexcept = default;
	collection_add_response& operator=(const collection_add_response &rhs) = default;
	collection_add_response& operator=(collection_add_response &&rhs) noexcept = default;

	int instance_id;
	platform::string_t resource_url;
};

} // namespace discogs
} // namespace parser
