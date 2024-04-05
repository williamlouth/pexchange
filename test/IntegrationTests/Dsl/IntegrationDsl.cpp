//
// Created by will on 03/04/24.
//

#include "IntegrationDsl.h"

#include <nlohmann/json.hpp>

namespace integration {
	bool IntegrationDsl::createUser(const pex::UserId& user)
	{
		exchange_.addUser(user);
		nlohmann::json logon;
		logon["type"] = "LogOn";
		logon["Username"] = user;
		return sendMessage(logon.dump(), user) == "Logon successfull";
	}
	std::string IntegrationDsl::createOrder(const pex::UserId& user,
		const pex::RoomId& room,
		const pex::Decimal& px,
		const pex::Decimal& sz,
		const pex::ClOrdId& clOrdId)
	{
		nlohmann::json message;
		message["type"] = "NewOrderSingle";
		message["price"] = toString(px);
		message["size"] = toString(sz);
		message["instrument"] = room;
		message["ClOrdId"] = clOrdId;
		return sendMessage(message.dump(), user);
	}
	std::string IntegrationDsl::sendMessage(const std::string& message, const pex::UserId& user)
	{
		if(!users_.contains(user))
		{
			users_.insert(std::make_pair(user, lastConnectionNumber_++));
		}
		return exchange_.onMessage(users_.at(user), message);
	}
	bool IntegrationDsl::userContainsFullFill(const pex::UserId& user, const pex::ClOrdId& clOrdId, const pex::Decimal& fillAmount)
	{
		nlohmann::json message;
		message["type"] = "FullFill";
		message["ClOrdId"] = clOrdId;
		message["FillAmount"] = toString(fillAmount);
		return userMessageContains(user, message.dump());
	}
	bool IntegrationDsl::userMessageContains(const pex::UserId& user, const std::string& message)
	{
		if(!users_.contains(user))
		{
			return false;
		}
		return exchange_.connectionMessageContains(users_.at(user), message);
	}
	void IntegrationDsl::addRoom(const pex::RoomId& room)
	{
		exchange_.addRoom(room);
	}
} // integration