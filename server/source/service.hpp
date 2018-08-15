//
// Created by liuchengde on 2018/7/15.
//
#ifndef SERVER_SERVICE_H
#define SERVER_SERVICE_H

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <functional>
#include "router.hpp"
#include "util.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using namespace web::http;

class service
{
public:
  service(router &r);
  static void stacktrace(http_request message);
  static void resigter(http_request message);
  static void result(http_request message);
  static void test(http_request message);
  static mongocxx::client conn;
};
#endif //SERVER_SERVICE_H
