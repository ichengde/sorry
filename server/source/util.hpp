//
// Created by liuchengde on 2018/7/16.
//

#ifndef SERVER_UTIL_H
#define SERVER_UTIL_H

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>

using namespace web::http;

class util
{
public:
  static std::map<utility::string_t, utility::string_t> getParams(http_request message);

  static utility::string_t getPath(http_request message);
};

#endif //SERVER_UTIL_H
