/* clang-format off */
#pragma once
#include <string>
#include <vector>

#include "class_common.hpp"
#include "paginate.hpp"
#include "base_classes.hpp"

namespace discogs {
namespace parser {

class price {
public:
	price(){}
	~price(){}
	price(const price &rhs) = default;
	price(price &&rhs) noexcept = default;
	price& operator=(const price &rhs) = default;
	price& operator=(price &&rhs) noexcept = default;

	platform::string_t value;
	platform::string_t currency;
};


class seller_stats {
public:
	seller_stats():total(0){}
	~seller_stats(){}
	seller_stats(const seller_stats &rhs) = default;
	seller_stats(seller_stats &&rhs) noexcept = default;
	seller_stats& operator=(const seller_stats &rhs) = default;
	seller_stats& operator=(seller_stats &&rhs) noexcept = default;

	int total;
	platform::string_t rating;
	platform::string_t stars;
};


class seller {
public:
	seller():id(0),uid(0){}
	~seller(){}
	seller(const seller &rhs) = default;
	seller(seller &&rhs) noexcept = default;
	seller& operator=(const seller &rhs) = default;
	seller& operator=(seller &&rhs) noexcept = default;

	int id;
	int uid;
	platform::string_t username;
	platform::string_t url;
	platform::string_t html_url;
	platform::string_t shipping;
	platform::string_t payment;
	platform::string_t avatar_url;
	platform::string_t resource_url;
	seller_stats stats_;
};


class release_stats_data {
public:
	release_stats_data():in_collection(0),in_wantlist(0){}
	~release_stats_data(){}
	release_stats_data(const release_stats_data &rhs) = default;
	release_stats_data(release_stats_data &&rhs) noexcept = default;
	release_stats_data& operator=(const release_stats_data &rhs) = default;
	release_stats_data& operator=(release_stats_data &&rhs) noexcept = default;

	int in_collection;
	int in_wantlist;
};


class release_stats {
public:
	release_stats(){}
	~release_stats(){}
	release_stats(const release_stats &rhs) = default;
	release_stats(release_stats &&rhs) noexcept = default;
	release_stats& operator=(const release_stats &rhs) = default;
	release_stats& operator=(release_stats &&rhs) noexcept = default;

	release_stats_data user;
	release_stats_data community;
};


class market_release {
public:
	market_release():id(0),year(0){}
	~market_release(){}
	market_release(const market_release &rhs) = default;
	market_release(market_release &&rhs) noexcept = default;
	market_release& operator=(const market_release &rhs) = default;
	market_release& operator=(market_release &&rhs) noexcept = default;

	int id;
	int year;
	platform::string_t description;
	platform::string_t format;
	platform::string_t catalog_number;
	platform::string_t artist;
	platform::string_t title;
	platform::string_t resource_url;
	platform::string_t thumbnail;
	std::vector<common::image> images;
	release_stats stats;
};


class converted_shipping_price {
public:
	converted_shipping_price():curr_id(0){}
	~converted_shipping_price(){}
	converted_shipping_price(const converted_shipping_price &rhs) = default;
	converted_shipping_price(converted_shipping_price &&rhs) noexcept = default;
	converted_shipping_price& operator=(const converted_shipping_price &rhs) = default;
	converted_shipping_price& operator=(converted_shipping_price &&rhs) noexcept = default;

	int curr_id;
	platform::string_t curr_abbr;
	platform::string_t formatted;
	platform::string_t value;
};


class original_shipping_price {
public:
	original_shipping_price():curr_id(0){}
	~original_shipping_price(){}
	original_shipping_price(const original_shipping_price &rhs) = default;
	original_shipping_price(original_shipping_price &&rhs) noexcept = default;
	original_shipping_price& operator=(const original_shipping_price &rhs) = default;
	original_shipping_price& operator=(original_shipping_price &&rhs) noexcept = default;

	int curr_id;
	platform::string_t curr_abbr;
	platform::string_t formatted;
	platform::string_t value;
	converted_shipping_price converted;
};


class shipping_price {
public:
	shipping_price(){}
	~shipping_price(){}
	shipping_price(const shipping_price &rhs) = default;
	shipping_price(shipping_price &&rhs) noexcept = default;
	shipping_price& operator=(const shipping_price &rhs) = default;
	shipping_price& operator=(shipping_price &&rhs) noexcept = default;

	platform::string_t currency;
	platform::string_t value;
};


class listing {
public:
	listing():in_cart(false),allow_offers(false),audio(false),id(0){}
	~listing(){}
	listing(const listing &rhs) = default;
	listing(listing &&rhs) noexcept = default;
	listing& operator=(const listing &rhs) = default;
	listing& operator=(listing &&rhs) noexcept = default;

	bool in_cart;
	bool allow_offers;
	bool audio;
	int id;
	platform::string_t status;
	platform::string_t ships_from;
	platform::string_t uri;
	platform::string_t comments;
	platform::string_t sleeve_condition;
	platform::string_t resource_url;
	platform::string_t condition;
	platform::string_t posted;
	original_shipping_price original_shipping_price_;
	price price_;
	shipping_price shipping_price_;
	seller seller_;
	market_release release;
	original_shipping_price original_price_;
};


class market_listing {
public:
	market_listing(){}
	~market_listing(){}
	market_listing(const market_listing &rhs) = default;
	market_listing(market_listing &&rhs) noexcept = default;
	market_listing& operator=(const market_listing &rhs) = default;
	market_listing& operator=(market_listing &&rhs) noexcept = default;

	std::vector<listing> listings;
	paginate::pagination pages;
};

} // namespace discogs
} // namespace parser
