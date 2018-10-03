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
#include "file.hpp"

class Env
{
public:
	static Env &Instance();
private:
	Env();
	Env(Env const &);
	Env &operator=(Env const &);
	~Env() {};
};

static Env *mySetting;

static mongocxx::client conn;

class mongo
{
public:
	static void write(const web::json::value &data, std::string collectionName = "log");
	static bsoncxx::v_noabi::document::value result(std::map<utility::string_t, utility::string_t> &params);
};

#endif //MONGO_H
