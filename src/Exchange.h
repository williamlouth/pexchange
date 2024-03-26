//
// Created by will on 24/03/24.
//

#pragma once
#include <map>
#include <UserManager.h>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;
	class Room;

	class Exchange {
    public:
		Exchange();

		void addRoom(const RoomId& roomId);
    private:
		void execute(const Bid& bid, const Ask& ask, const Decimal& size);
		void addBid(const RoomId& roomId, const Bid& bid);
		void addAsk(const RoomId& roomId, const Ask& ask);
		void deleteBid(const RoomId& roomId, const OrderId& id);
		void deleteAsk(const RoomId& roomId, const OrderId& id);

        std::map<RoomId,Room> rooms_;
		UserManager userManager_;
};

} // pex
