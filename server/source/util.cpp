//
// Created by liuchengde on 2018/7/16.
//

#include "util.hpp"

std::map<utility::string_t, utility::string_t> util::getParams(web::http::http_request &message)
{
    auto query = web::uri::decode(message.relative_uri().query());
    auto params = web::uri::split_query(query);
    return params;
}

utility::string_t util::getPath(web::http::http_request &message)
{
    auto relativePath = web::uri::decode(message.relative_uri().path());
    return relativePath;
}

std::map<std::string, std::string> util::readConfigFile()
{
    const char *homedir = getenv("HOME");
    std::string configPath{homedir};
    configPath += "/js-sorry.cnf";

    std::map<std::string, std::string> configParmasMap{};
    std::ifstream configFile(configPath);
    std::stringstream configStream;
    configStream << configFile.rdbuf();

    std::string configKey;
    std::string configValue;

    while (configStream >> configKey >> configValue, !configStream.eof())
    {
        std::cout << configKey << " " << configValue << std::endl;
        configParmasMap[configKey] = configValue;
    }

    if (configFile.fail())
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
    }

    configFile.close();

    return configParmasMap;
    // file.open()
    // std::basic_ifstream::open(configPath)
}
