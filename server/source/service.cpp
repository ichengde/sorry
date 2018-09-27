//
// Created by liuchengde on 2018/7/15.
//
#include "service.hpp"
#include "user/register.hpp"

service::service(router &r)
{
  mongocxx::instance inst{};
  r.get("/result", &(service::result));
  r.get("/test", &service::test);

  r.post("/stacktrace", &service::stacktrace);
  r.post("/consolelog", &service::consolelog);
  r.post("/login", &service::login);
  r.post("/registerUser", &service::registerUser);
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
  try
  {

    auto resp = resp::get();
    resp.headers().add("Content-Type", "application/json");
    auto doc = mongo::result(params);
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

    auto data = message.extract_json().get();
    bool isSuccess = user::registerNew(data);

    if (isSuccess == true)
    {
      auto response = resp::get(status_codes::OK);

      response.set_body("successfully");
      message.reply(response);
    }
    else
    {
      auto response = resp::get(status_codes::InternalError);

      response.set_body("error");
      message.reply(response);
    }
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
