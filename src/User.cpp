//
// Created by will on 26/03/24.
//

#include "User.h"

#include <OrderIdGenerator.h>
#include <UserOrder.h>

#include "Order.h"

namespace pex
{
	User::User(OrderIdGenerator& orderIdGenerator,
	           const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
	           const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk,
	           const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteBid,
	           const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk
	           )
		: addBid_{addBid}
		, addAsk_{addAsk}
		, deleteBid_{deleteBid}
		, deleteAsk_{deleteAsk}
		, orderIdGenerator_{orderIdGenerator}
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
	void User::deleteOrder(const ClOrdId& clOrdId)
	{
		if(auto itr = bids_.find(clOrdId); itr != bids_.end())
		{
			deleteBid_(itr->second.roomId, itr->second.id);
		}
		else if(auto itr = asks_.find(clOrdId); itr != asks_.end())
		{
			deleteAsk_(itr->second.roomId, itr->second.id);
		}
	}
	void User::createOrder(const ClOrdId& clOrdId,
	                       const RoomId& roomId,
	                       const TimePoint& timeStamp,
	                       const Decimal& px,
	                       const Decimal& sz)
	{
		const auto orderId = orderIdGenerator_.getNextOrderId();
		if(sz > 0)
		{
			const auto bid = Bid{orderId, timeStamp, px, sz};
			const auto userOrder = UserOrder{orderId, timeStamp, px, sz, roomId};
			bids_.insert({clOrdId,userOrder});
			addBid_(roomId, bid);
		}
		else
		{
			const auto ask = Ask{orderId, timeStamp, px, -sz};
			const auto userOrder = UserOrder{orderId, timeStamp, px, sz, roomId};
			asks_.insert({clOrdId,userOrder});
			addAsk_(roomId, ask);
		}
	}
} // pex