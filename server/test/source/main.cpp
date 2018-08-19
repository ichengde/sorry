#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <doctest.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

void resigter()
{
    http_client resigter_client(U("http://127.0.0.1/"));

    web::json::value userData = web::json::value::object();
    userData["user"] = web::json::value::string("js-sorry-1");
    userData["password"] = web::json::value::string("js-sorry-password");

    resigter_client.request(
                       methods::POST,
                       uri_builder(U("/resigter")).set_port(5525).to_string(),
                       userData)
        .then([=](http_response response) {
            printf("Response status code %u returned.\n", response.status_code());

            CHECK(true);
        });
}

TEST_CASE("resigter")
{
    resigter();
}

TEST_CASE("testing the factorial function")
{
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}