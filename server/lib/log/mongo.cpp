#include "sorry/log/mongo.hpp"


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
	~Env() {};
};

static Env * mySetting = Env::Instance();

static mongocxx::client conn = mongocxx::client{ mongocxx::uri{
	"mongodb://" + mySetting.user + ":" + mySetting.password +
	"@" + mySetting.host + "/js-sorry"} };

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
			auto isHasProject = data.has_field("project");

			for (auto b : stack.as_array())
			{
				for (auto dd : b.as_object())
				{
					builder << dd.first << dd.second.serialize();
				}
				if (isHasProject == true)
				{
					auto project = data.at("project");
					builder << "project" << project.serialize();
				}
				bsoncxx::document::value log = builder << bsoncxx::builder::stream::finalize;
				logs.push_back(log);
			}
			collection.insert_many(logs);
		}
	}

	static bsoncxx::v_noabi::document::value result(std::map<utility::string_t, utility::string_t> &params)
	{

		auto count = params.find("count");
		int resultCount = count != params.end() ? std::stoi(count->second) : 10;

		auto build = bsoncxx::builder::stream::document{};
		auto collection = conn["js-sorry"]["log"];
		auto pipe = mongocxx::pipeline{};
		auto logs = collection.aggregate(pipe.limit(resultCount));

		auto in_array = build << "stack" << bsoncxx::builder::stream::open_array;
		for (auto log : logs)
		{
			in_array << log;
		}
		auto after_array = in_array << bsoncxx::builder::stream::close_array;
		auto doc = after_array << bsoncxx::builder::stream::finalize;

		return doc;
	}
};