//
// Created by will on 24/03/24.
//

#pragma once
#include <ExchangeInternal.h>
#include <Server.h>

namespace pex {
	class Bid;
	class Ask;
	class Room;

	class Exchange : public ExchangeInternal{
    public:
		Exchange();

		void stopListening();
		void runServer();

	protected:
		void sendMessage(const ConnectionId& connection, const std::string& message) override;

	public:
		Server server_;
};

} // pex
