//
// Created by liuchengde on 2018/7/15.
//

#include "router.hpp"

router::router(web::http::experimental::listener::http_listener &listener) {
    this->listener = &listener;

    this->getHandler = [this](web::http::http_request message) {
        util utility;
        auto path = utility.getPath(message);

        for (auto hd: this->getHandleSet) {
            if (hd.first == path) {
                hd.second(message);
            }
        }

        auto response = web::http::http_response(web::http::status_codes::NotFound);
        message.reply(response);
    };

    this->postHandler = [this](web::http::http_request message) {
        util utility;
        auto params = utility.getParams(message);
        auto path = utility.getPath(message);

        for (auto hd: this->postHandleSet) {
            if (hd.first == path) {
                hd.second(message);
            }
        }

        auto response = web::http::http_response(web::http::status_codes::OK);
        response.headers().add("Access-Control-Allow-Origin", "*");
        response.headers().add("Access-Control-Allow-Headers", "*");

        message.reply(response);

    };

    this->optionHandler = [](web::http::http_request message) {
        auto response = web::http::http_response(web::http::status_codes::OK);

        response.headers().add("Access-Control-Allow-Origin", "*");
        response.headers().add("Access-Control-Allow-Headers", "*");

        message.reply(response);

    };

    listener.support(web::http::methods::GET, this->getHandler);
    listener.support(web::http::methods::POST, this->postHandler);
    listener.support(web::http::methods::OPTIONS, this->optionHandler);
}

web::uri router::getEndPoint() {
    return web::uri_builder{}.set_scheme("http")
            .set_host("0.0.0.0").set_port(5525).set_path("/").to_uri();
}

void router::get(const std::string &path, const std::function<void(web::http::http_request)> &handler) {
    this->getHandleSet[path] = handler;
}

void router::post(const std::string &path, const std::function<void(web::http::http_request)> &handler) {
    this->postHandleSet[path] = handler;
}



