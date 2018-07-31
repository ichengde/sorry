//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"
#include "setting.hpp"
#include "util.hpp"

mongocxx::client service::conn = mongocxx::client{mongocxx::uri{
    "mongodb://" + setting::database::user + ":" + setting::database::password +
    "@" + setting::database::host + "/js-sorry"}};

service::service(router &r)
{
  mongocxx::instance inst{};
  r.post("/stacktrace", &service::stacktrace);
  r.get("/result", &(service::result));
};

void service::stacktrace(http_request message)
{
  try
  {
    util utilTool{};

    auto builder = bsoncxx::builder::stream::document{};
    auto collection = service::conn["js-sorry"]["log"];
    // should add collection one.
    auto data = message.extract_json().get();
    if (data.is_object())
    {
      auto stack = data.at("stack");
      for (auto b : stack.as_array())
      {
        for (auto dd : b.as_object())
        {
          std::cout << dd.first << dd.second << std::endl;
          builder << dd.first << dd.second.to_string();
        }
        bsoncxx::document::value di = builder << bsoncxx::builder::stream::finalize;
        collection.insert_one(di.view());
      }
    }

    /*
auto cursor = collection.find({});

for (auto&& doc : cursor) {
std::cout << bsoncxx::to_json(doc) << std::endl;
}
*/
    auto response = http_response(status_codes::OK);
    response.headers().add("Access-Control-Allow-Origin", "*");
    response.headers().add("Access-Control-Allow-Headers", "*");
    message.reply(response);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred connect database: %s\n"
              << e.what();
  }
  message.reply(status_codes::InternalError);
}

void service::test(http_request message)
{
  http_response b;
  b.set_status_code(status_codes::OK);
  b.set_body("my test");
  message.reply(b);
}

void service::result(http_request message)
{
  http_response b;

  auto build = bsoncxx::builder::stream::document{};
  auto collection = service::conn["js-sorry"]["log"];

  auto ans = collection.find({});

  auto in_array = build << "stack" << bsoncxx::builder::stream::open_array;
  for (auto a : ans)
  {
    in_array << a;
  }
  auto after_array = in_array << bsoncxx::builder::stream::close_array;
  auto doc = after_array << bsoncxx::builder::stream::finalize;

  b.set_status_code(status_codes::OK);
  b.set_body(bsoncxx::to_json(doc));
  message.reply(b);
}