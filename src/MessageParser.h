//
// Created by will on 28/03/24.
//

#pragma once
#include <functional>
#include <string>
#include <nlohmann/json_fwd.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class NewOrderSingle;
	class CancelOrder;

class MessageParser {
    public:
	explicit MessageParser(std::function<std::string(const UserId&,const NewOrderSingle&)> newOrderSingle,
		std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder,
		std::function<void(const ConnectionId&, const std::string&)> sendMessage
		);
	std::string onRawMessage(ConnectionId connectionId, const std::string& rawMessage);
	void fullyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& decimal);
	void partiallyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& decimal);

private:
	std::string onJsonMessage(ConnectionId connectionId, const nlohmann::json& message);
	std::string onNewOrderSingle(const UserId& user, const nlohmann::json& message);
	std::string onCancelOrder(const UserId& user, const nlohmann::json& message);
	std::string onLogOn(ConnectionId connectionId, const nlohmann::json& message);

	std::function<std::string(const UserId&, const NewOrderSingle&)> newOrderSingle_;
	std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder_;

	std::function<void(const ConnectionId&, const std::string&)> sendMessage_;

	std::map<ConnectionId, UserId> connections_;

};

} // pex
