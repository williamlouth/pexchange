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
		std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder);
	std::string onRawMessage(const std::string& rawMessage);
private:
	std::string onJsonMessage(const nlohmann::json& message);
	std::string onNewOrderSingle(const nlohmann::json& message);
	std::string onCancelOrder(const nlohmann::json& message);

	std::function<std::string(const UserId&, const NewOrderSingle&)> newOrderSingle_;
	std::function<std::string(const UserId&, const CancelOrder&)> cancelOrder_;

};

} // pex
