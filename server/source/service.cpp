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
  r.post("/consolelog", &service::consolelog);
  r.get("/result", &(service::result));
  r.post("/login", &service::login);
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
      auto isHasProject = data.has_string_field("project");

      for (auto b : stack.as_array())
      {
        for (auto dd : b.as_object())
        {
          builder << dd.first << dd.second.to_string();
        }
        if (isHasProject == true)
        {
          auto project = data.at("project");
          builder << "project" << project.to_string();
        }
        bsoncxx::document::value log = builder << bsoncxx::builder::stream::finalize;
        logs.push_back(log);
      }
      collection.insert_many(logs);
    }

    auto response = resp::get();
    message.reply(response);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred" << e.what() << std::endl;
  }
  message.reply(status_codes::InternalError);
}


void service::stacktrace(const http_request &message)
{
  try
  {
    util utilTool{};

    auto builder = bsoncxx::builder::stream::document{};
    auto collection = service::conn["js-sorry"]["consolelog"];
    std::vector<bsoncxx::document::value> logs;

    // should add collection one.
    auto data = message.extract_json().get();
    if (data.is_object())
    {
      auto stack = data.at("stack");
      auto isHasProject = data.has_string_field("project");

      for (auto b : stack.as_array())
      {
        for (auto dd : b.as_object())
        {
          builder << dd.first << dd.second.to_string();
        }
        if (isHasProject == true)
        {
          auto project = data.at("project");
          builder << "project" << project.to_string();
        }
        bsoncxx::document::value log = builder << bsoncxx::builder::stream::finalize;
        logs.push_back(log);
      }
      collection.insert_many(logs);
    }

    auto response = resp::get();
    message.reply(response);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred" << e.what() << std::endl;
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

    auto resp = resp::get();
    resp.headers().add("Content-Type", "application/json");
    resp.set_body(bsoncxx::to_json(doc));
    message.reply(resp);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred"
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
      auto response = resp::get(status_codes::InternalError);

      response.set_body("error");
      message.reply(response);
    }

    auto response = resp::get(status_codes::OK);

    response.set_body("successfully");
    message.reply(response);
  }
  catch (std::exception &e)
  {

    if (strstr(e.what(), "E11000"))
    {
      auto response = resp::get(status_codes::InternalError);

      response.set_body("user exist");
      message.reply(response);
    }
    else
    {
      std::cout << "Error occurred"
                << e.what()
                << std::endl;
    }
  }
  message.reply(status_codes::InternalError);
}

void service::login(const http_request &message)
{
  util utilTool{};
  auto data = message.extract_json().get();

  message.reply(status_codes::OK);
}