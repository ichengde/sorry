#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <codecvt>

int main() {
    const auto uri = web::uri_builder{}.set_scheme("http")
            .set_host("0.0.0.0").set_port(5525).set_path("/").to_uri();


    web::http::experimental::listener::http_listener listener{uri};
    auto handle = [](web::http::http_request message) {
        auto relativePath = web::uri::decode(message.relative_uri().path());
        auto query = web::uri::decode(message.relative_uri().query());
        auto params = web::uri::split_query(query);
        auto path = web::uri::split_path(relativePath);

        auto errorHandle = [=](pplx::task<void> result) {
            try {
                std::cout << message.method();
                result.wait();
                std::cout << "Sending succeeded" << std::endl;
            }
            catch (std::exception &e) {
                std::cout << "Error occurred sending response: %s\n" << e.what();
            }
        };

        if (!path.empty()) {
            int i = 0;
            auto resp = web::json::value::array();
            for (auto it:path) {
                resp[i] = web::json::value::string(it);
                i++;
            }

            for (auto p:params) {
                resp[i] = web::json::value::string(p.first);
                i++;
                resp[i] = web::json::value::string(p.second);
                i++;
            }

            message.reply(web::http::status_codes::OK, resp).then(errorHandle);
        } else {
            auto content = web::json::value::object();
            content["version"] = web::json::value::string("0.0.1");
            content["status"] = web::json::value::string("ready!");

            auto data = message.extract_json().get();
            if (data.is_object()) {
                auto stack = data.at("stack");
                for (auto b :stack.as_array()) {
                    for (auto dd: b.as_object()) {
                        std::cout << dd.first << "=" << dd.second << std::endl;
                    }
                }
            }
            auto response = web::http::http_response(web::http::status_codes::OK);

            response.headers().add("Access-Control-Allow-Origin", "*");
            response.headers().add("Access-Control-Allow-Headers", "*");

            response.set_body(content);

            for (auto p:params) {

                std::cout << p.first << ' ' << p.second << std::endl;
            }

            message.reply(response).then(errorHandle);
        }

    };
    listener.support(web::http::methods::GET, handle);
    listener.support(web::http::methods::POST, handle);
    listener.support(web::http::methods::OPTIONS, handle);

    std::cout << "sorry server start" << std::endl;
    listener.open().wait();

    std::string line;
    std::getline(std::cin, line);

    listener.close().wait();
}