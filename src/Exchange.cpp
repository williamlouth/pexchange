//
// Created by will on 24/03/24.
//

#include "Exchange.h"

#include <Room.h>
#include <Order.h>

namespace pex
{
	Exchange::Exchange()
		: userManager_{
			[this](const RoomId& roomId, const Bid& bid) { this->addBid(roomId, bid); },
			[this](const RoomId& roomId, const Ask& ask) { this->addAsk(roomId, ask); },
			[this](const RoomId& roomId, const OrderId& id) { this->deleteBid(roomId, id); },
			[this](const RoomId& roomId, const OrderId& id) { this->deleteAsk(roomId, id); }
		}
	{
	}
	void Exchange::addRoom(const RoomId& roomId)
	{
		rooms_.insert({roomId, Room{[this](const Bid& bid, const Ask& ask, const Decimal& size){this->execute(bid, ask, size);}}} );
	}
	void Exchange::execute(const Bid&, const Ask&, const Decimal&)
	{
	}
	void Exchange::addBid(const RoomId& roomId, const Bid& bid)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.addBid(bid);
		}
	}
	void Exchange::addAsk(const RoomId& roomId, const Ask& ask)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.addAsk(ask);
		}
	}
	void Exchange::deleteBid(const RoomId& roomId, const OrderId& id)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.deleteBid(id);
		}
	}
	void Exchange::deleteAsk(const RoomId& roomId, const OrderId& id)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.deleteAsk(id);
		}
	}
} // pex