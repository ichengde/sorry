#ifndef MONGO_H
#define MONGO_H

#include <string>
#include <iostream>

#include <cpprest/json.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "../util.hpp"

namespace log
{

class Env
{
  public:
    static Env &Instance()
    {
        static Env theEnv;
        return theEnv;
    }

    std::string host = "";
    std::string user = "";
    std::string password = "";
    /* more (non-static) functions here */

  private:
    Env()
    {
        std::map<std::string, std::string> p = util::readConfigFile();
        std::map<std::string, std::string> *dd = &p;
        std::map<std::string, std::string Env::*> v = {
            {"host", &Env::host},
            {"username", &Env::user},
            {"password", &Env::password},
        };

        for (auto vpair : v)
        {
            auto ans = p.find(vpair.first);
            if (ans != p.end())
            {
                this->*(vpair.second) = ans->second;
            }
        }
    };
    Env(Env const &);
    Env &operator=(Env const &);
    ~Env(){};
};

} // namespace log

static log::Env &mySetting = log::Env::Instance();

static mongocxx::client conn = mongocxx::client{mongocxx::uri{
    "mongodb://" + mySetting.user + ":" + mySetting.password +
    "@" + mySetting.host + "/js-sorry"}};

class mongo
{
  public:
    static void write(const web::json::value &data, std::string collectionName = "log")
    {

        auto builder = bsoncxx::builder::stream::document{};
        auto collection = conn["js-sorry"][collectionName];
        // is choice another collection, such as consolelog
        std::vector<bsoncxx::document::value> logs;

        if (data.is_object())
        {
            auto stack = data.at("stack");
            auto isHasProject = data.has_string_field("project");

            for (auto b : stack.as_array())
            {
                for (auto dd : b.as_object())
                {
                    builder << dd.first << dd.second.to_string();
                }
                if (isHasProject == true)
                {
                    auto project = data.at("project");
                    builder << "project" << project.to_string();
                }
                bsoncxx::document::value log = builder << bsoncxx::builder::stream::finalize;
                logs.push_back(log);
            }
            collection.insert_many(logs);
        }
    }
};

#endif //MONGO_H
