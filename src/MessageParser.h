//
// Created by will on 28/03/24.
//

#pragma once
#include <functional>
#include <string>
#include <nlohmann/json_fwd.hpp>
#include <websocketpp/common/connection_hdl.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class NewOrderSingle;
	class CancelOrder;

class MessageParser {
    public:
	explicit MessageParser(std::function<std::string(const UserId&,const NewOrderSingle&)> newOrderSingle,
		std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder);
	std::string onRawMessage(websocketpp::connection_hdl connectionHandle, const std::string& rawMessage);
private:
	std::string onJsonMessage(websocketpp::connection_hdl connectionHandle, const nlohmann::json& message);
	std::string onNewOrderSingle(const UserId& user, const nlohmann::json& message);
	std::string onCancelOrder(const UserId& user, const nlohmann::json& message);
	std::string onLogOn(websocketpp::connection_hdl connectionHandle, const nlohmann::json& message);

	std::function<std::string(const UserId&, const NewOrderSingle&)> newOrderSingle_;
	std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder_;

	std::map<websocketpp::connection_hdl, UserId, std::owner_less<>> connections_;

};

} // pex
