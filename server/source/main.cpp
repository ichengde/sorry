#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <codecvt>
#include "router.hpp"

int main() {

    web::http::experimental::listener::http_listener listener{r.getEndPoint()};

    router r{listener};
    try {
        std::cout << "sorry server start" << std::endl;
        listener.open().wait();

        std::string line;
        std::getline(std::cin, line);

        listener.close().wait();
    }
    catch (std::exception &e) {
        std::cout << "Error occurred sending response: %s\n" << e.what();
    }


}