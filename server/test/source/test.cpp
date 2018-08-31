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
                if (response.extract_string().get() == "successfully" ||
                    response.extract_string().get() == "user exist")
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

int stacktrace(string_t stack)
{
    web::json::value data = web::json::value::parse(stack);

    try
    {
        http_client registerUser_client("http://127.0.0.1:5525/");

        registerUser_client.request(methods::POST, uri_builder(U("/stacktrace")).to_string(), data)
            .then([=](http_response response) {
                if (response.status_code() == status_codes::OK)
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

TEST_CASE("stacktrace")
{

    SUBCASE("stacktrace without project")
    {
        stacktrace("{\"stack\":[{\"columnNumber\":17,\"lineNumber\":3,\"fileName\":\"http://127.0.0.1:8080/test.js\",\"functionName\":\"stack3\",\"source\":\"    at stack3 (http://127.0.0.1:8080/test.js:3:17)\"},{\"columnNumber\":5,\"lineNumber\":9,\"fileName\":\"http://127.0.0.1:8080/test.js\",\"functionName\":\"stack2\",\"source\":\"    at stack2 (http://127.0.0.1:8080/test.js:9:5)\"},{\"columnNumber\":5,\"lineNumber\":15,\"fileName\":\"http://127.0.0.1:8080/test.js\",\"functionName\":\"stack1\",\"source\":\"    at stack1 (http://127.0.0.1:8080/test.js:15:5)\"},{\"columnNumber\":5,\"lineNumber\":35,\"fileName\":\"http://127.0.0.1:8080/test.js\",\"functionName\":\"window.onload\",\"source\":\"    at window.onload (http://127.0.0.1:8080/test.js:35:5)\"}]}");
    }
    SUBCASE("stacktrace with project")
    {
        stacktrace("{\"stack\":[{\"columnNumber\":17,\"lineNumber\":3,\"fileName\":\"http://127.0.0.1:8080/test.js\",\"functionName\":\"stack3\",\"source\":\"    at stack3 (http://127.0.0.1:8080/test.js:3:17)\"}],\"project\":\"test_my\"}");
    }
}
