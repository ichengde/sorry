//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"

service::service(router &r)
{
  mongocxx::instance inst{};
  r.post("/stacktrace", &service::stacktrace);
  r.post("/consolelog", &service::consolelog);
  r.get("/result", &(service::result));
  r.post("/login", &service::login);
  r.post("/registerUser", &service::registerUser);
  r.post("/test", &service::test);
};

void service::stacktrace(const http_request &message)
{
  try
  {
    util utilTool{};

    auto data = message.extract_json().get();
    // record stack trace;
    mongo::write(data);
    auto response = resp::get();
    message.reply(response);
  }
  catch (std::exception &e)
  {
    std::cout << "Error occurred" << e.what() << std::endl;
  }
  message.reply(status_codes::InternalError);
}

void service::consolelog(const http_request &message)
{
  try
  {
    util utilTool{};
    auto data = message.extract_json().get();
    // write log to consolelog collection name
    mongo::write(data, "consolelog");
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

    // auto build = bsoncxx::builder::stream::document{};
    // auto collection = service::conn["js-sorry"]["log"];
    // auto pipe = mongocxx::pipeline{};
    // auto logs = collection.aggregate(pipe.limit(resultCount));

    // auto in_array = build << "stack" << bsoncxx::builder::stream::open_array;
    // for (auto log : logs)
    // {
    //   in_array << log;
    // }
    // auto after_array = in_array << bsoncxx::builder::stream::close_array;
    // auto doc = after_array << bsoncxx::builder::stream::finalize;

    auto resp = resp::get();
    resp.headers().add("Content-Type", "application/json");
    // resp.set_body(bsoncxx::to_json(doc));
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
    // auto collection = service::conn["js-sorry"]["user"];
    // std::vector<bsoncxx::document::value> user;

    // auto data = message.extract_json().get();
    // std::cout << data.to_string();
    // if (data.is_object())
    // {
    //   auto stack = data.at("user");
    //   auto userData = data.as_object();

    //   builder << "user" << userData.at("user").to_string();
    //   builder << "password" << userData.at("password").to_string();
    //   bsoncxx::document::value emitUserData = builder << bsoncxx::builder::stream::finalize;
    //   collection.insert_one(emitUserData.view());
    // }
    // else
    // {
    //   auto response = resp::get(status_codes::InternalError);

    //   response.set_body("error");
    //   message.reply(response);
    // }

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

void service::test(const http_request &message)
{
  file::write();
  message.reply(status_codes::OK);

}
