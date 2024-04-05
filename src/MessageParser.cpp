//
// Created by will on 28/03/24.
//

#include "MessageParser.h"

#include <Messages/CancelOrder.h>
#include <Messages/NewOrderSingle.h>
#include <nlohmann/json.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex
{
	MessageParser::MessageParser(std::function<std::string(const UserId&, const NewOrderSingle&)> newOrderSingle,
	                             std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder,
	                             std::function<void(const ConnectionId&, const std::string&)> sendMessage
	                             )
		: newOrderSingle_{std::move(newOrderSingle)}
		, cancelOrder_{std::move(cancelOrder)}
		, sendMessage_{std::move(sendMessage)}
	{
	}
	std::string MessageParser::onRawMessage(ConnectionId connectionId, const std::string& rawMessage)
	{
		try
		{
			return onJsonMessage(connectionId, nlohmann::json::parse(rawMessage));
		}
		catch (nlohmann::json::parse_error const & e)
		{
			return "parse error of incoming message";
		}
		catch (...)
		{	return "Unknown error";}
	}
	void MessageParser::fullyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& fillAmount)
	{
		if(const auto itr = std::ranges::find_if(connections_, [&user](const auto& p){return p.second == user;}); itr != connections_.end())
		{
			nlohmann::json message;
			message["type"] = "FullFill";
			message["ClOrdId"] = clOrdId;
			message["FillAmount"] = toString(fillAmount);
			sendMessage_(itr->first, message.dump());
		}
	}
	void MessageParser::partiallyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& fillAmount)
	{
		if(const auto itr = std::ranges::find_if(connections_, [&user](const auto& p){return p.second == user;}); itr != connections_.end())
		{
			nlohmann::json message;
			message["type"] = "PartialFill";
			message["ClOrdId"] = clOrdId;
			message["FillAmount"] = toString(fillAmount);
			sendMessage_(itr->first, message.dump());
		}
	}
	std::string MessageParser::onJsonMessage(ConnectionId connectionId, const nlohmann::json& message)
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
				return onLogOn(connectionId, message);
			}

			if (auto user = connections_.find(connectionId); user == connections_.end())
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

		return newOrderSingle_(user, NewOrderSingle{user, clOrdId, roomId, TimePoint{}, px, sz}); //TODO: sort out timepoint
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
	std::string MessageParser::onLogOn(ConnectionId connectionId, const nlohmann::json& message)
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
		connections_[connectionId] = userId;
		return "Logon successfull";
	}
} // pex