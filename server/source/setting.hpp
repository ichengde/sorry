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
    auto p = util::readConfigFile();
    std::vector<std::string> v = {"host", "username", "password"};

  };                                     // ctor hidden
  database(database const &);            // copy ctor hidden
  database &operator=(database const &); // assign op. hidden
  ~database(){};                         // dtor hidden
};

} // namespace setting

#endif //SERVER_SETTING_H
