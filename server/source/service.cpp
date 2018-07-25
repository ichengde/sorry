//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"
#include "setting.hpp"

mongocxx::client service::conn = mongocxx::client{mongocxx::uri{"mongodb://"+setting::database::user+":"+setting::database::password+"@"+setting::database::host+"/js-sorry"}};

service::service(router &r) {
    mongocxx::instance inst{};
    r.get("/stacktrace", &service::getCollection);
    // r.get("/test", &(service::test));
};

void service::getCollection(http_request message) {
    try {
        bsoncxx::builder::stream::document document{};

        auto collection = service::conn["js-sorry"]["testcollection"];
        document << "hello" << "world";

        collection.insert_one(document.view());
/*         
        auto cursor = collection.find({});

        for (auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        } 
*/
        message.reply(status_codes::OK);
    } 
    catch (std::exception &e) {
        std::cout << "Error occurred connect database: %s\n" << e.what();
    }
    message.reply(status_codes::InternalError);

}

void service::test(http_request message) {
    http_response b;
    b.set_status_code(status_codes::OK);
    b.set_body("my test");
    message.reply(b);
}