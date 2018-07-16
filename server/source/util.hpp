//
// Created by liuchengde on 2018/7/16.
//

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

class util {
public:
    static std::map<utility::string_t, utility::string_t> getParams(web::http::http_request message);
    static std::vector<utility::string_t> getPath(web::http::http_request message);
};

#endif //SERVER_UTIL_H
