//
// Created by will on 03/04/24.
//

#include "IntegrationDsl.h"

#include <nlohmann/json.hpp>

namespace integration {
	void IntegrationDsl::createUser(const std::string& user)
	{
		nlohmann::json logon;
		logon["type"] = "Logon";
		logon["Username"] = user;
		sendMessage(logon.dump(), user);
	}
	std::string IntegrationDsl::sendMessage(const std::string& message, const std::string& user)
	{
		if(!users_.contains(user))
		{
			users_.insert(std::make_pair(user, lastConnectionNumber_++));
		}
		return exchange_.onMessage(users_.at(user), message);
	}
} // integration