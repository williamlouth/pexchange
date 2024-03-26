//
// Created by will on 24/03/24.
//

#include "Exchange.h"

#include <Room.h>
#include <Order.h>

namespace pex {
	void Exchange::addRoom(const RoomId& roomId)
	{
		rooms_.insert({roomId, Room{[this](const Bid& bid, const Ask& ask, const Decimal& size){this->execute(bid, ask, size);}}} );
	}
	void Exchange::execute(const Bid&, const Ask&, const Decimal&)
	{
	}
} // pex