//
// Created by will on 28/03/24.
//

#include "MessageParser.h"

#include <CancelOrder.h>
#include <iostream>
#include <NewOrderSingle.h>
#include <nlohmann/json.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex
{
	MessageParser::MessageParser(std::function<std::string(const UserId&, const NewOrderSingle&)> newOrderSingle,
	                             std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder)
		: newOrderSingle_{std::move(newOrderSingle)}
		, cancelOrder_{std::move(cancelOrder)}
	{
	}
	std::string MessageParser::onRawMessage(websocketpp::connection_hdl connectionHandle, const std::string& rawMessage)
	{
		try
		{
			return onJsonMessage(connectionHandle, nlohmann::json::parse(rawMessage));
		}
		catch (nlohmann::json::parse_error const & e)
		{
			return "parse error of incoming message";
		}
		catch (...)
		{	return "Unknown error";}
	}
	std::string MessageParser::onJsonMessage(websocketpp::connection_hdl connectionHandle, const nlohmann::json& message)
	{
		if(const auto messageTypeItr = message.find("type"); messageTypeItr == message.end())
		{
			return "message is missing type";
		}
		else
		{
			const auto messageType = messageTypeItr->get<std::string>();
			if (messageType == "LogOn")
			{
				return onLogOn(connectionHandle, message);
			}

			if (auto user = connections_.find(connectionHandle); user == connections_.end())
			{
				return "Not Logged In";
			}
			else
			{
				if (messageType == "NewOrderSingle")
				{
					return onNewOrderSingle(user->second, message);
				}
				else if (messageType == "CancelOrder")
				{
					return onCancelOrder(user->second, message);
				}
				return "Unsupported message type: " + messageType;
			}
		}
	}
	std::string MessageParser::onNewOrderSingle(const UserId& user, const nlohmann::json& message)
	{
		Decimal px;
		Decimal sz;
		RoomId roomId;
		ClOrdId clOrdId;
		if(const auto price = message.find("price"); price == message.end())
		{
			return "NewOrderSingle missing price";
		}
		else
		{
			px = Decimal{price->get<std::string>()};
		}
		if(const auto size = message.find("size"); size == message.end())
		{
			return "NewOrderSingle missing size";
		}
		else
		{
			sz = Decimal{size->get<std::string>()};
		}
		if(const auto room = message.find("instrument");  room == message.end())
		{
			return "NewOrderSingle missing instrument";
		}
		else
		{
			roomId = room->get<std::string>();
		}
		if(const auto clId = message.find("ClOrdId"); clId == message.end())
		{
			return "NewOrderSingle missing ClOrdId";
		}
		else
		{
			clOrdId = ClOrdId{clId->get<uint64_t>()};
		}

		return newOrderSingle_(user, NewOrderSingle{clOrdId, roomId, TimePoint{}, px, sz}); //TODO: sort out timepoint
	}
	std::string MessageParser::onCancelOrder(const UserId& user, const nlohmann::json& message)
	{
		ClOrdId clOrdId;
		if(const auto clId = message.find("ClOrdId"); clId == message.end())
		{
			return "CancelOrder missing ClOrdId";
		}
		else
		{
			clOrdId = ClOrdId{clId->get<uint64_t>()};
		}
		return cancelOrder_(user, CancelOrder{clOrdId});
	}
	std::string MessageParser::onLogOn(websocketpp::connection_hdl connectionHandle, const nlohmann::json& message)
	{
		UserId userId;
		if(const auto user = message.find("Username"); user == message.end())
		{
			return "Logon missing Username";
		}
		else
		{
			userId = UserId{user->get<std::string>()};
		}
		connections_[connectionHandle] = userId;
		return "Logon successful";
	}
} // pex