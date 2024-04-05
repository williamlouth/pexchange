//
// Created by will on 03/04/24.
//

#include "IntegrationExchange.h"

namespace integration {
	std::string IntegrationExchange::onMessage(pex::ConnectionId connectionId, const std::string& message)
	{
		return messageParser_.onRawMessage(std::move(connectionId), message);
	}
} // integration