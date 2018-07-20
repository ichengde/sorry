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


class service {
public:
    service(router);

    static std::function<void(web::http::http_request)> handle;
    static std::function<void(web::http::http_request)> stackTrace;
    static std::function<void(web::http::http_request)> optionHandle;
};
#endif //SERVER_SERVICE_H
