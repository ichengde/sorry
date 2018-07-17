//
// Created by liuchengde on 2018/7/15.
//

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include "service.hpp"
#include "util.hpp"

#ifndef SERVER_ROUTER_H
#define SERVER_ROUTER_H

class router {
public:
    router(web::http::experimental::listener::http_listener &listener);

    std::map<std::string, std::function<void(web::http::http_request)>> getHandleSet;
    std::map<std::string, std::function<void(web::http::http_request)>> postHandleSet;

    static web::uri getEndPoint();

    void get(const std::string &path, const std::function<void(web::http::http_request)> &handler);

    void post(const std::string &path, const std::function<void(web::http::http_request)> &handler);


    std::function<void(web::http::http_request)> getHandler;
    std::function<void(web::http::http_request)> postHandler;
    std::function<void(web::http::http_request)> optionHandler;

private:
    web::http::experimental::listener::http_listener *listener;

};

#endif //SERVER_ROUTER_H
