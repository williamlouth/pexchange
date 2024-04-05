//
// Created by will on 26/03/24.
//

#include "User.h"
#include <algorithm>

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
	           const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk,
	           const std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)>& fullyFilled,
	           const std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)>& partiallyFilled
	           )
		: addBid_{addBid}
		, addAsk_{addAsk}
		, deleteBid_{deleteBid}
		, deleteAsk_{deleteAsk}
		, fullyFilled_{fullyFilled}
		, partiallyFilled_{partiallyFilled}
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
		if(const auto itr = bids_.find(cancelOrder.clOrdId); itr != bids_.end())
		{
			deleteBid_(itr->second.roomId, itr->second.id);
			return "Successfully deleted order: " + cancelOrder.clOrdId;
		}
		else if(const auto askItr = asks_.find(cancelOrder.clOrdId);  askItr != asks_.end())
		{
			deleteAsk_( askItr->second.roomId,  askItr->second.id);
			return "Successfully deleted order: " + cancelOrder.clOrdId;
		}
		else
		{
			return "ClOrdId not found: " + cancelOrder.clOrdId;
		}
	}
	void User::executeBid(const Bid& bid, const Decimal& fillAmount)
	{
		if(const auto itr = std::ranges::find_if(bids_, [&bid](const auto& p){return p.second.id == bid.id;}); itr != bids_.end())
		{
			if(bid.remains() == 0)
			{
				fullyFilled_(bid.user, itr->first, fillAmount);
				bids_.erase(itr);
			}
			else
			{
				partiallyFilled_(bid.user, itr->first, fillAmount);
			}
		}
	}
	void User::executeAsk(const Ask& ask, const Decimal& fillAmount)
	{
		if(const auto itr = std::ranges::find_if(asks_, [&ask](const auto& p){return p.second.id == ask.id;}); itr != asks_.end())
		{
			if(ask.remains() == 0)
			{
				fullyFilled_(ask.user, itr->first, fillAmount);
				bids_.erase(itr);
			}
			else
			{
				partiallyFilled_(ask.user, itr->first, fillAmount);
			}
		}
	}
	void User::createOrder(const NewOrderSingle& newOrderSingle)
	{
		const auto orderId = orderIdGenerator_.getNextOrderId();
		if(newOrderSingle.sz > 0)
		{
			const auto bid = Bid{orderId, newOrderSingle.user, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz};
			const auto userOrder = UserOrder{orderId, newOrderSingle.user, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz, newOrderSingle.roomId};
			bids_.insert({newOrderSingle.clOrdId,userOrder});
			addBid_(newOrderSingle.roomId, bid);
		}
		else
		{
			const auto ask = Ask{orderId, newOrderSingle.user, newOrderSingle.timeStamp, newOrderSingle.px, -newOrderSingle.sz};
			const auto userOrder = UserOrder{orderId, newOrderSingle.user, newOrderSingle.timeStamp, newOrderSingle.px, newOrderSingle.sz, newOrderSingle.roomId};
			asks_.insert({newOrderSingle.clOrdId,userOrder});
			addAsk_(newOrderSingle.roomId, ask);
		}
	}
} // pex