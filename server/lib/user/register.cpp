#includ "sorry/user/register.hpp"

namespace user
{
	bool registerNew(web::json::value &data)
	{
		auto builder = bsoncxx::builder::stream::document{};
		auto collection = conn["js-sorry"]["user"];
		std::vector<bsoncxx::document::value> user;

		std::cout << data.serialize();
		if (data.is_object())
		{
			auto stack = data.at("user");
			auto userData = data.as_object();

			builder << "user" << userData.at("user").serialize();
			builder << "password" << userData.at("password").serialize();
			bsoncxx::document::value emitUserData = builder << bsoncxx::builder::stream::finalize;
			collection.insert_one(emitUserData.view());
			return true;
		}
		return false;
	}
} // namespace user