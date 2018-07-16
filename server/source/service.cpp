//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"
#include "util.hpp"

std::function<void(web::http::http_request)> service::handle = [](web::http::http_request message) {
    util utility;
    auto params = utility.getParams(message);
    auto path = utility.getPath(message);

    if (!path.empty()) {
        int i = 0;
        auto resp = web::json::value::array();
        for (auto it:path) {
            resp[i] = web::json::value::string(it);
            i++;
        }

        for (auto p:params) {
            resp[i] = web::json::value::string(p.first);
            i++;
            resp[i] = web::json::value::string(p.second);
            i++;
        }

    }
    message.reply(web::http::status_codes::OK);

};

std::function<void(web::http::http_request)> service::stackTrace = [](web::http::http_request message) {
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

std::function<void(web::http::http_request)> service::optionHandle = [](web::http::http_request message) {
    auto response = web::http::http_response(web::http::status_codes::OK);

    response.headers().add("Access-Control-Allow-Origin", "*");
    response.headers().add("Access-Control-Allow-Headers", "*");

    message.reply(response);
};