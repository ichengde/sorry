//
// Created by liuchengde on 2018/7/15.
//

#include "router.hpp"

router::router(web::http::experimental::listener::http_listener &listener) {
    this->listener = &listener;

    this->getHandler = [](web::http::http_request message) {
        util utility;
        auto params = utility.getParams(message);
        auto path = utility.getPath(message);
    };

    this->postHandler = [](web::http::http_request message) {
        util utility;
        auto params = utility.getParams(message);
        auto path = utility.getPath(message);

        auto content = web::json::value::object();
        content["version"] = web::json::value::string("0.0.1");
        content["status"] = web::json::value::string("ready!");

        auto data = message.extract_json().get();
        if (data.is_object()) {
            auto stack = data.at("stack");
            for (auto b :stack.as_array()) {
                for (auto dd: b.as_object()) {
                    std::cout << dd.first << "=" << dd.second << std::endl;
                }
            }
        }
        auto response = web::http::http_response(web::http::status_codes::OK);

        response.headers().add("Access-Control-Allow-Origin", "*");
        response.headers().add("Access-Control-Allow-Headers", "*");

        response.set_body(content);

        for (auto p:params) {

            std::cout << p.first << ' ' << p.second << std::endl;
        }

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



