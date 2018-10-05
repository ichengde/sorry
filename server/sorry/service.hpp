//
// Created by liuchengde on 2018/7/15.
//
#ifndef SORRY_SERVER_SERVICE_H
#define SORRY_SERVER_SERVICE_H

#include <string>
#include <iostream>

#include <cpprest/http_listener.h>
#include <cpprest/http_headers.h>
#include <cpprest/json.h>
#include <functional>
#include "sorry/router.hpp"
#include "sorry/util.hpp"
#include "sorry/setting.hpp"


#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


using namespace web::http;

class Env
{
public:
	static Env &Instance()
	{
		static Env theEnv;
		return theEnv;
	};
	std::string host = "";
	std::string user = "";
	std::string password = "";
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
	~Env() {};
};

class resp
{
public:
  inline static http_response get(status_code m_status = status_codes::OK)
  {
    auto m_resp = http_response(m_status);

    m_resp.headers().add("Content-Type", "application/json");
    m_resp.headers().add("Access-Control-Allow-Origin", "*");
    m_resp.headers().add("Access-Control-Allow-Headers", "*");
    return m_resp;
  }
};

class service
{
public:
  service(router &r);
  static void stacktrace(const http_request &message);
  static void registerUser(const http_request &message);
  static void result(const http_request &message);
  static void login(const http_request &message);
  static void consolelog(const http_request &message);
  static void test(const http_request &message);
};
#endif //SORRY_SERVER_SERVICE_H
