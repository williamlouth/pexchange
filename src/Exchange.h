//
// Created by will on 24/03/24.
//

#pragma once
#include <map>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;
	class Room;

	class Exchange {
    public:

		void addRoom(const RoomId& roomId);
    private:
		void execute(const Bid& bid, const Ask& ask, const Decimal& size);

        std::map<RoomId,Room> rooms_;
};

} // pex
