//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"
#include "setting.hpp"
#include "util.hpp"
setting::database &mySetting = setting::database::Instance();
mongocxx::client service::conn = mongocxx::client{mongocxx::uri{
    "mongodb://" + mySetting.user + ":" + mySetting.password +
    "@" + mySetting.host + "/js-sorry"}};

service::service(router &r)
{
  mongocxx::instance inst{};
  r.post("/stacktrace", &service::stacktrace);
  r.get("/result", &(service::result));
  // r.post("/login", &service::login);
  r.post("/registerUser", &service::registerUser);
};

void service::stacktrace(const http_request &message)
{
  try
  {
    util utilTool{};

    auto builder = bsoncxx::builder::stream::document{};
    auto collection = service::conn["js-sorry"]["log"];
    std::vector<bsoncxx::document::value> logs;

    // should add collection one.
    auto data = message.extract_json().get();
    if (data.is_object())
    {
      auto stack = data.at("stack");
      auto project = data.at("project");
      for (auto b : stack.as_array())
      {
        for (auto dd : b.as_object())
        {
          std::cout << dd.first << dd.second << std::endl;
          builder << dd.first << dd.second.to_string();
        }
        if (project.is_string())
        {
          builder << "project" << project.to_string();
        }
        bsoncxx::document::value log = builder << bsoncxx::builder::stream::finalize;
        logs.push_back(log);
      }
      collection.insert_many(logs);
    }

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

void service::result(const http_request &message)
{
  util u;
  auto params = u.getParams(message);
  auto count = params.find("count");
  int resultCount = count != params.end() ? std::stoi(count->second) : 10;

  try
  {
    http_response resp;

    auto build = bsoncxx::builder::stream::document{};
    auto collection = service::conn["js-sorry"]["log"];
    auto pipe = mongocxx::pipeline{};
    auto logs = collection.aggregate(pipe.limit(resultCount));

    auto in_array = build << "stack" << bsoncxx::builder::stream::open_array;
    for (auto log : logs)
    {
      in_array << log;
    }
    auto after_array = in_array << bsoncxx::builder::stream::close_array;
    auto doc = after_array << bsoncxx::builder::stream::finalize;

    resp.headers().add("Content-Type", "application/json");
    resp.headers().add("Access-Control-Allow-Origin", "*");
    resp.headers().add("Access-Control-Allow-Headers", "*");
    resp.set_status_code(status_codes::OK);
    resp.set_body(bsoncxx::to_json(doc));
    message.reply(resp);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred connect database: %s\n"
              << e.what()
              << std::endl
              << strstr(e.what(), "connection timeout")
              << std::endl;

    http_response resp;
    resp.set_status_code(status_codes::InternalError);
    resp.set_body(bsoncxx::to_json(bsoncxx::builder::stream::document{} << "code"
                                                                        << "error"
                                                                        << bsoncxx::builder::stream::finalize));
    message.reply(resp);
  }
}

void service::registerUser(const http_request &message)
{
  try
  {
    util utilTool{};

    auto builder = bsoncxx::builder::stream::document{};
    auto collection = service::conn["js-sorry"]["user"];
    std::vector<bsoncxx::document::value> user;

    auto data = message.extract_json().get();
    std::cout << data.to_string();
    if (data.is_object())
    {
      auto stack = data.at("user");
      auto userData = data.as_object();

      builder << "user" << userData.at("user").to_string();
      builder << "password" << userData.at("password").to_string();
      bsoncxx::document::value emitUserData = builder << bsoncxx::builder::stream::finalize;
      collection.insert_one(emitUserData.view());
    }
    else
    {
      auto response = http_response(status_codes::InternalError);
      response.headers().add("Access-Control-Allow-Origin", "*");
      response.headers().add("Access-Control-Allow-Headers", "*");
      response.set_body("error");
      message.reply(response);
    }

    auto response = http_response(status_codes::OK);
    response.headers().add("Access-Control-Allow-Origin", "*");
    response.headers().add("Access-Control-Allow-Headers", "*");
    response.set_body("successfully");
    message.reply(response);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred connect database: %s\n"
              << e.what();
  }
  message.reply(status_codes::InternalError);
}