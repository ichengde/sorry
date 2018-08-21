// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <codecvt>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
// #include <doctest.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

// int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

void resigter()
{
    http_client resigter_client(U("http://127.0.0.1/"));

    web::json::value userData = web::json::value::object();
    userData["user"] = web::json::value::string("js-sorry-1");
    userData["password"] = web::json::value::string("js-sorry-password");
    // MESSAGE("resigter");
    try
    {

        http_request request(methods::POST);

        uri_builder ret;

        ret.set_path("http://127.0.0.1:5525/resigter");

        request.set_request_uri(ret.to_uri());
        request.headers().add(header_names::accept, L"application/json");
        request.set_body(userData);

        resigter_client.request(request)
            .then([=](http_response response) {
                // MESSAGE("response");

                printf("Response status code %u returned.\n", response.status_code());
            });
    }
    catch (std::exception &e)
    {
        // MESSAGE("Error occurred");
        std::cout << e.what() << std::endl;
    }
}
int main() {
    resigter();
    return 0;
}
// TEST_CASE("resigter")
// {
//     resigter();
//     // CHECK(true);
//     // resigter();
// }
