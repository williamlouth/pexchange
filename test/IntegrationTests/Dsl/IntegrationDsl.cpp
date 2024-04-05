//
// Created by will on 03/04/24.
//

#include "IntegrationDsl.h"

#include <nlohmann/json.hpp>

namespace integration {
	void IntegrationDsl::createUser(const pex::UserId& user)
	{
		nlohmann::json logon;
		logon["type"] = "Logon";
		logon["Username"] = user;
		sendMessage(logon.dump(), user);
	}
	std::string IntegrationDsl::sendMessage(const std::string& message, const pex::UserId& user)
	{
		if(!users_.contains(user))
		{
			users_.insert(std::make_pair(user, lastConnectionNumber_++));
		}
		return exchange_.onMessage(users_.at(user), message);
	}
	bool IntegrationDsl::userMessageContains(const pex::UserId& user, const std::string& message)
	{
		if(!users_.contains(user))
		{
			return false;
		}
		return exchange_.connectionMessageContains(users_.at(user), message);
	}
} // integration