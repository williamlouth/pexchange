//
// Created by will on 03/04/24.
//

#include "IntegrationExchange.h"
#include <Room.h>
#include <algorithm>

namespace integration {
	std::string IntegrationExchange::onMessage(pex::ConnectionId connectionId, const std::string& message)
	{
		return messageParser_.onRawMessage(std::move(connectionId), message);
	}

	void IntegrationExchange::sendMessage(const pex::ConnectionId& connection, const std::string& message)
	{
		connectionMessages_[connection].push_back(message);
	}
    bool IntegrationExchange::connectionMessageContains(const pex::ConnectionId& connection, const std::string& message)
	{
		if(!connectionMessages_.contains(connection))
		{
			return false;
		}
		return std::ranges::find(connectionMessages_.at(connection), message) != connectionMessages_.at(connection).end();
	}

} // integration