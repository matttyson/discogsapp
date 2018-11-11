/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"

namespace discogs {
namespace parser {

class folder_response {
public:
	folder_response():id(0),count(0){}
	~folder_response(){}
	folder_response(const folder_response &rhs) = default;
	folder_response(folder_response &&rhs) noexcept = default;
	folder_response& operator=(const folder_response &rhs) = default;
	folder_response& operator=(folder_response &&rhs) noexcept = default;

	int id;
	int count;
	platform::string_t name;
	platform::string_t resource_url;
};

} // namespace discogs
} // namespace parser
