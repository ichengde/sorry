//
// Created by liuchengde on 2018/7/16.
//

#ifndef SORRY_SERVER_UTIL_H
#define SORRY_SERVER_UTIL_H

#include <iostream>
#include <string>
#include <map>
#include <clocale>
#include <cstdlib>
#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>

using namespace web::http;

class util
{
public:
  static std::map<utility::string_t, utility::string_t> getParams(const http_request &message);

  static utility::string_t getPath(const http_request &message);

  static std::map<std::string, std::string> readConfigFile();

  static std::string &to_string(std::string &dest, std::wstring const &src)
  {
    std::setlocale(LC_CTYPE, "");

    size_t const mbs_len = wcstombs(NULL, src.c_str(), 0);
    std::vector<char> tmp(mbs_len + 1);
    wcstombs(&tmp[0], src.c_str(), tmp.size());

    dest.assign(tmp.begin(), tmp.end() - 1);

    return dest;
  }

  static std::wstring &to_wstring(std::wstring &dest, std::string const &src)
  {
    //   std::setlocale(LC_CTYPE, "");
    std::setlocale(LC_CTYPE, "zh_CN");

    size_t const wcs_len = mbstowcs(NULL, src.c_str(), 0);
    std::vector<wchar_t> tmp(wcs_len + 1);
    mbstowcs(&tmp[0], src.c_str(), src.size());

    dest.assign(tmp.begin(), tmp.end() - 1);

    return dest;
  }
};

#endif //SORRY_SERVER_UTIL_H
