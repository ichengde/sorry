//
// Created by liuchengde on 2018/7/15.
//
#ifndef SORRY_SERVER_ROUTER_H
#define SORRY_SERVER_ROUTER_H

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include "sorry/util.hpp"

using namespace web::http;
using namespace web::http::experimental::listener;
class router {
public:
    router(http_listener &listener);

    std::map<std::string, std::function<void(http_request)>> getHandleSet;
    std::map<std::string, std::function<void(http_request)>> postHandleSet;
    
    static web::uri getEndPoint();

    void get(const std::string &path, const std::function<void(http_request)> &handler);
    void post(const std::string &path, const std::function<void(http_request)> &handler);

    std::function<void(http_request)> getHandler;
    std::function<void(http_request)> postHandler;
    std::function<void(http_request)> optionHandler;

private:
    http_listener *listener;
};

#endif //SORRY_SERVER_ROUTER_H
