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

void resigter()
{
    web::json::value userData = web::json::value::object();
    userData["user"] = web::json::value::string("js-sorry-1");
    userData["password"] = web::json::value::string("js-sorry-password");

    try
    {
        web::http::uri uri(U("http://127.0.0.1:5525/resigter"));
        std::cout << uri.to_string() << std::endl;

        http_request request(methods::POST);
        request.set_request_uri(uri);
        request.set_body(userData);
        request.headers().add("Content-Type", "application/json");

        http_client resigter_client(uri);

        resigter_client.request(request)
            .then([=](http_response response) {
                if (response.extract_string().get() == "successfully")
                {
                    CHECK(true);
                }
                else
                {
                    CHECK(false);
                }

                printf("Response body %s returned.\n", response.extract_string().get().c_str());
            })
            .wait();
    }
    catch (const web::http::http_exception &e)
    {
        CHECK(false);

        std::cout << e.what() << std::endl;
        // if (is_timeout())
        // {
        //     // Since this test depends on an outside server sometimes it sporadically can fail due to timeouts
        //     // especially on our build machines.
        //     return;
        // }
        throw;
    }
    // catch (std::exception &e)
    // {
    //     // MESSAGE("Error occurred");
    //     std::cout << e.what() << std::endl;
    // }
}
// int main()
// {
//     resigter();
//     return 0;
// }
TEST_CASE("resigter")
{
    resigter();
    // resigter();
}
