//
// Created by liuchengde on 2018/7/15.
//

#include "router.hpp"

router::router(http_listener &listener) {
    this->listener = &listener;

    this->getHandler = [this](http_request message) {
        util utility;
        auto path = utility.getPath(message);

        for (auto hd: this->getHandleSet) {
            if (hd.first == path) {
                hd.second(message);
            }
        }

        auto response = http_response(status_codes::NotFound);
        message.reply(response);
    };

    this->postHandler = [this](http_request message) {
        util utility;
        auto params = utility.getParams(message);
        auto path = utility.getPath(message);

        for (auto hd: this->postHandleSet) {
            if (hd.first == path) {
                hd.second(message);
            }
        }

        auto response = http_response(status_codes::OK);
        response.headers().add("Access-Control-Allow-Origin", "*");
        response.headers().add("Access-Control-Allow-Headers", "*");

        message.reply(response);

    };

    this->optionHandler = [](http_request message) {
        auto response = http_response(status_codes::OK);

        response.headers().add("Access-Control-Allow-Origin", "*");
        response.headers().add("Access-Control-Allow-Headers", "*");

        message.reply(response);

    };

    listener.support(methods::GET, this->getHandler);
    listener.support(methods::POST, this->postHandler);
    listener.support(methods::OPTIONS, this->optionHandler);
}

web::uri router::getEndPoint() {
    return web::uri_builder{}.set_scheme("http")
            .set_host("0.0.0.0").set_port(5525).set_path("/").to_uri();
}

void router::get(const std::string &path, const std::function<void(http_request)> &handler) {
    this->getHandleSet[path] = handler;
}

void router::post(const std::string &path, const std::function<void(http_request)> &handler) {
    this->postHandleSet[path] = handler;
}



