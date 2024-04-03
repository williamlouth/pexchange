//
// Created by will on 24/03/24.
//

#pragma once
#include <map>
#include <MessageParser.h>
#include <Server.h>
#include <UserManager.h>
#include <nlohmann/json_fwd.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;
	class Room;

	class Exchange {
    public:
		Exchange();

		void stopListening();
		void addRoom(const RoomId& roomId);
		void runServer();
    private:
		void execute(const Bid& bid, const Ask& ask, const Decimal& size);
		void addBid(const RoomId& roomId, const Bid& bid);
		void addAsk(const RoomId& roomId, const Ask& ask);
		void deleteBid(const RoomId& roomId, const OrderId& id);
		void deleteAsk(const RoomId& roomId, const OrderId& id);

		std::string newOrderSingle(const UserId& user, const NewOrderSingle& newOrderSingle);
		std::string cancelOrder(const UserId& user, const CancelOrder& cancelOrder);

        std::map<RoomId,Room> rooms_;
		UserManager userManager_;
		MessageParser messageParser_;
		Server server_;
};

} // pex
