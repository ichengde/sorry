//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"

service::service(router &r) {
    
}


std::function<void(web::http::http_request)> service::handle = [](web::http::http_request message) {
    util utility;
    auto params = utility.getParams(message);
    auto path = utility.getPath(message);

};

std::function<void(web::http::http_request)> service::stackTrace = [](web::http::http_request message) {


};

std::function<void(web::http::http_request)> service::optionHandle = [](web::http::http_request message) {

};