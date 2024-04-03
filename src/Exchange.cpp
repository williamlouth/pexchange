//
// Created by will on 24/03/24.
//

#include "Exchange.h"
#include "Room.h"

namespace pex
{
	Exchange::Exchange()
		: server_{[this](auto handle,  const auto& message) { return messageParser_.onRawMessage(handle, message); }}
	{
	}
	void Exchange::stopListening()
	{
		server_.stopListening();
	}
	void Exchange::runServer()
	{
		server_.run();
	}
} // pex