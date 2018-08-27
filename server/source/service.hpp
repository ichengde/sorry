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

class resp
{
public:
  inline static http_response get(status_code m_status = status_codes::OK)
  {
    auto resp = http_response(m_status);

    resp.headers().add("Content-Type", "application/json");
    resp.headers().add("Access-Control-Allow-Origin", "*");
    resp.headers().add("Access-Control-Allow-Headers", "*");
    return resp;
  }
};

class service
{
public:
  service(router &r);
  static void stacktrace(const http_request &message);
  static void registerUser(const http_request &message);
  static void result(const http_request &message);
  static void login(const http_request &message);
  static mongocxx::client conn;
};
#endif //SERVER_SERVICE_H
