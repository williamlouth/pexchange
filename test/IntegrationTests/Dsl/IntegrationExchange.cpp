//
// Created by will on 03/04/24.
//

#include "IntegrationExchange.h"
#include <Room.h>

namespace integration {
	std::string IntegrationExchange::onMessage(pex::ConnectionId connectionId, const std::string& message)
	{
		return messageParser_.onRawMessage(std::move(connectionId), message);
	}

	void IntegrationExchange::sendMessage(const pex::ConnectionId&, const std::string&)
	{
	}
} // integration