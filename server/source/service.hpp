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
#include "setting.hpp"
#include "log/mongo.hpp"

using namespace web::http;

class resp
{
public:
  inline static http_response get(status_code m_status = status_codes::OK)
  {
    auto m_resp = http_response(m_status);

    m_resp.headers().add("Content-Type", "application/json");
    m_resp.headers().add("Access-Control-Allow-Origin", "*");
    m_resp.headers().add("Access-Control-Allow-Headers", "*");
    return m_resp;
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
  static void consolelog(const http_request &message);
};
#endif //SERVER_SERVICE_H
