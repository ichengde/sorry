//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"

std::function<void(web::http::http_request)> service::handle = [](web::http::http_request message) {
    util utility;
    auto params = utility.getParams(message);
    auto path = utility.getPath(message);

};

std::function<void(web::http::http_request)> service::stackTrace = [](web::http::http_request message) {


};

std::function<void(web::http::http_request)> service::optionHandle = [](web::http::http_request message) {

};

service::service(router) {

}

service::getCollection() {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}
