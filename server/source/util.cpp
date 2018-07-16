//
// Created by liuchengde on 2018/7/16.
//

#include "util.hpp"

std::map<utility::string_t, utility::string_t> util::getParams(web::http::http_request message) {
    auto query = web::uri::decode(message.relative_uri().query());
    auto params = web::uri::split_query(query);
    return params;
}

std::vector<utility::string_t> util::getPath(web::http::http_request message) {
    auto relativePath = web::uri::decode(message.relative_uri().path());
    auto path = web::uri::split_path(relativePath);
    return path;
}
