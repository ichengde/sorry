#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <codecvt>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include "router.hpp"
#include "service.hpp"

using namespace web::http;

int main()
{
    experimental::listener::http_listener listener{router::getEndPoint()};

    router r{listener};
    service s{r};
    try
    {
        std::cout << "sorry server start" << std::endl;
        listener.open().wait();

        std::string line;
        std::getline(std::cin, line);

        listener.close().wait();
    }
    catch (std::exception &e)
    {
        std::cout << "Error occurred sending response: %s\n"
                  << e.what();
    }
}


void registerUser()
{
    web::http::client::http_client registerUser_client(U("http://127.0.0.1/"));

    web::json::value userData = web::json::value::object();
    userData["user"] = web::json::value::string("js-sorry-1");
    userData["password"] = web::json::value::string("js-sorry-password");

    registerUser_client.request(
                       methods::POST,
                       uri_builder(U("/registerUser")).set_port(5525).to_string(),
                       userData)
        .then([=](http_response response) {
            printf("Response status code %u returned.\n", response.status_code());
        });
}