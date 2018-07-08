#include <iostream>
#include <cpprest/http_listener.h>

int main() {
    const auto uri = web::uri_builder{}.set_scheme("http")
            .set_host("0.0.0.0").set_port(5525).set_path("/").to_uri();


    web::http::experimental::listener::http_listener listener{uri};

    listener.support(web::http::methods::GET, [](web::http::http_request message) {
        auto relativePath = web::uri::decode(message.relative_uri().path());
        auto path = web::uri::split_path(relativePath);
        if (!path.empty()) {
            int i = 0;
            auto resp = web::json::value::array();
            for (auto it :path) {
                resp[i] = web::json::value::string(it);
                i++;
            }

            message.reply(web::http::status_codes::OK, resp).then([](pplx::task<void> result) {
                try {
                    result.wait();
                    std::cout << "Sending succeeded" << std::endl;
                }
                catch (std::exception &e) {
                    std::cout << "Error occurred sending response: %s\n" << e.what();
                }
            });
        } else {
            auto response = web::json::value::object();
            response["version"] = web::json::value::string("0.0.1");
            response["status"] = web::json::value::string("ready!");
            message.reply(web::http::status_codes::OK, response);
        }

    });

    std::cout << "sorry server start" << std::endl;
    listener.open().wait();

    std::string line;
    std::getline(std::cin, line);

    listener.close().wait();
}