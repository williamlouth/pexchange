//
// Created by will on 26/03/24.
//

#include "User.h"

#include <NewOrderSingle.h>
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
	void User::addOrder(const NewOrderSingle& newOrderSingle)
	{
		createOrder(newOrderSingle);
		//TODO: Run checks on NOS
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
	void User::createOrder(const NewOrderSingle& newOrderSingle)
	{
		const auto orderId = orderIdGenerator_.getNextOrderId();
		if(newOrderSingle.sz > 0)
		{
			const auto bid = Bid{orderId, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz};
			const auto userOrder = UserOrder{orderId, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz, newOrderSingle.roomId};
			bids_.insert({newOrderSingle.clOrdId,userOrder});
			addBid_(newOrderSingle.roomId, bid);
		}
		else
		{
			const auto ask = Ask{orderId, newOrderSingle.timeStamp, newOrderSingle.px, -newOrderSingle.sz};
			const auto userOrder = UserOrder{orderId, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz, newOrderSingle.roomId};
			asks_.insert({newOrderSingle.clOrdId,userOrder});
			addAsk_(newOrderSingle.roomId, ask);
		}
	}
} // pex