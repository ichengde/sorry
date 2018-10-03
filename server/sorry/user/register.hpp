#ifndef USER_H
#define USER_H
#include "../log/mongo.hpp"

namespace user
{
	bool registerNew(web::json::value &data);
} // namespace user

#endif //USER_H
