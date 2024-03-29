//
// Created by will on 26/03/24.
//

#include "User.h"

#include <Messages/CancelOrder.h>
#include <Messages/NewOrderSingle.h>
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
	std::string User::addOrder(const NewOrderSingle& newOrderSingle)
	{
		createOrder(newOrderSingle);
		//TODO: Run checks on NOS
		return "Successfully placed order: " + newOrderSingle.clOrdId;
	}
	std::string User::deleteOrder(const CancelOrder& cancelOrder)
	{
		if(auto itr = bids_.find(cancelOrder.clOrdId); itr != bids_.end())
		{
			deleteBid_(itr->second.roomId, itr->second.id);
			return "Successfully deleted order: " + cancelOrder.clOrdId;
		}
		else if(auto itr = asks_.find(cancelOrder.clOrdId); itr != asks_.end())
		{
			deleteAsk_(itr->second.roomId, itr->second.id);
			return "Successfully deleted order: " + cancelOrder.clOrdId;
		}
		else
		{
			return "ClOrdId not found: " + cancelOrder.clOrdId;
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