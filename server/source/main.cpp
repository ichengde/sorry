#include <iostream>
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

        std::cout << "sorry server close" << std::endl;
        listener.close().wait();
    }
    catch (std::exception &e)
    {
        std::cout << "Error occurred sending response: %s\n"
                  << e.what();
    }
}
