

#ifndef MONGO_H
#define MONGO_H

#include <string>
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "../util.hpp"

namespace log
{
//   static mongocxx::client conn;

database &mySetting = log::database::Instance();

mongocxx::client conn = mongocxx::client{mongocxx::uri{
    "mongodb://" + mySetting.user + ":" + mySetting.password +
    "@" + mySetting.host + "/js-sorry"}};

class mongo
{
  public:
    static void write(const web::value::json &data, std::string collectionName = "log")
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

class database
{
  public:
    static database &Instance()
    {
        static database theDatabase;
        return theDatabase;
    }

    std::string host = "";
    std::string user = "";
    std::string password = "";
    /* more (non-static) functions here */

  private:
    database()
    {
        std::map<std::string, std::string> p = util::readConfigFile();
        std::map<std::string, std::string> *dd = &p;
        std::map<std::string, std::string database::*> v = {
            {"host", &database::host},
            {"username", &database::user},
            {"password", &database::password},
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
    database(database const &);
    database &operator=(database const &);
    ~database(){};
};

} // namespace log
#endif //MONGO_H
