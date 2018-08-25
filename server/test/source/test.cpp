#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <codecvt>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <doctest.h>
#include <cpprest/http_msg.h>
using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int registerUser()
{
    web::json::value userData = web::json::value::object();
    userData["user"] = web::json::value::string("js-sorry-1");
    userData["password"] = web::json::value::string("js-sorry-password");
    try
    {
        http_client registerUser_client("http://127.0.0.1:5525/");

        registerUser_client.request(methods::POST, uri_builder(U("/registerUser")).to_string(), userData)
            .then([=](http_response response) {
                if (response.extract_string().get() == "successfully")
                {
                    CHECK(true);
                }
                else
                {
                    CHECK(false);
                }

                // printf("Response status %d\n", response.status_code());
                // printf("Response body %s returned.\n", response.extract_string().get().c_str());
            })
            .wait();
    }
    catch (const web::http::http_exception &e)
    {
        CHECK(false);

        std::cout << e.what() << std::endl;
        throw;
    }
    return 0;
}

TEST_CASE("registerUser")
{
    registerUser();
}

int result()
{

    try
    {
        http_client registerUser_client("http://127.0.0.1:5525/");

        http_request requestInfo(methods::GET);
        requestInfo.headers().set_content_type("application/json");

        registerUser_client.request(methods::GET, uri_builder(U("/result")).to_string())
            .then([=](http_response response) {
                CHECK(true);
            })
            .wait();
    }
    catch (const web::http::http_exception &e)
    {
        CHECK(false);

        std::cout << e.what() << std::endl;
        throw;
    }
    return 0;
}

TEST_CASE("result")
{
    result();
}