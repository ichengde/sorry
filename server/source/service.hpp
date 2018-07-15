//
// Created by liuchengde on 2018/7/15.
//
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <functional>

#ifndef SERVER_SERVICE_H
#define SERVER_SERVICE_H

class service {
public:
    static std::function<void(web::http::http_request)> handle;
    static std::function<void(web::http::http_request)> stacktrace;
};

#endif //SERVER_SERVICE_H
