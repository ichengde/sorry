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
        web::http::uri uri("http://127.0.0.1:5525/registerUser");

        http_request requestInfo(methods::POST);
        requestInfo.set_request_uri(uri);
        requestInfo.set_body(userData);

        for (auto dd : requestInfo.headers())
        {
            std::cout << dd.first << dd.second << std::endl;
        }
        std::cout << requestInfo.request_uri().host() << std::endl;
        std::cout << requestInfo.request_uri().port() << std::endl;
        std::cout << requestInfo.request_uri().path() << std::endl;
        std::cout << requestInfo.request_uri().query() << std::endl;
        http_client registerUser_client(uri);

        registerUser_client.request(requestInfo)
            .then([=](http_response response) {
                if (response.extract_string().get() == "successfully")
                {
                    CHECK(true);
                }
                else
                {
                    CHECK(false);
                }

                for (auto h : response.headers())
                {
                    std::cout << h.first << h.second << std::endl;
                }
                printf("Response status %d\n", response.status_code());
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
    return 0;
}
// int main()
// {
//     registerUser();
//     return 0;
// }
TEST_CASE("registerUser")
{
    registerUser();
    // registerUser();
}
