//
// Created by liuchengde on 2018/7/15.
//
#ifndef SERVER_SETTING_H
#define SERVER_SETTING_H
#include <string>
#include <iostream>
#include "util.hpp"

namespace setting
{

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

} // namespace setting

#endif //SERVER_SETTING_H
