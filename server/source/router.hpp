//
// Created by liuchengde on 2018/7/15.
//

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include "service.hpp"

#ifndef SERVER_ROUTER_H
#define SERVER_ROUTER_H

class router {
public:
    static web::uri getEndPoint();

    static void run(web::http::experimental::listener::http_listener &listener);
};

#endif //SERVER_ROUTER_H
