//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"

service::service(router &r) {
    r.get("/stacktrace", &(service::getCollection));
};

void service::getCollection(http_request message) {
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
