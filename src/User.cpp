//
// Created by will on 26/03/24.
//

#include "User.h"
#include "Order.h"

namespace pex {
	User::User(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid, const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk)
		: addBid_{addBid}
		, addAsk_{addAsk}
	{
	}
	void User::addOrder(const ClOrdId& clOrdId,
	                    const RoomId& roomId,
	                    const TimePoint& timeStamp,
	                    const Decimal& px,
	                    const Decimal& sz)
	{
		createOrder(clOrdId, roomId, timeStamp, px, sz);
	}
	void User::createOrder(const ClOrdId& clOrdId,
		const RoomId& roomId,
		const TimePoint& timeStamp,
		const Decimal& px,
		const Decimal& sz)
	{
		OrderId orderId{1}; //TODO: create a unique orderId Generator
		if(sz > 0)
		{
			auto bid = Bid{orderId, timeStamp, px, sz};
			bids_.insert({clOrdId,bid});
			addBid_(roomId, bid);
		}
		else
		{
			auto ask = Ask{orderId, timeStamp, px, -sz};
			asks_.insert({clOrdId,ask});
			addAsk_(roomId, ask);
		}
	}
} // pex