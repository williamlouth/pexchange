//
// Created by will on 24/03/24.
//

#include "Room.h"

#include "Order.h"

namespace pex {
	Room::Room(std::function<void(const Bid& bid, const Ask& ask, const Decimal& size)> execute)
		: execute_{std::move(execute)}
	{
	}
	void Room::addBid(const Bid& newOrder)
	{
		auto newOrderCopy = newOrder;
		while(newOrderCopy.remains() > 0 && !asks_.empty())
		{
			auto& asksFront = *asks_.begin();
			if(newOrderCopy.px >= asksFront.px)
			{
				if(asksFront.remains() > newOrderCopy.remains())
				{
					execute_(newOrderCopy, asksFront, newOrderCopy.remains());
					auto nodeHandle = asks_.extract(asks_.begin());
					nodeHandle.value().filled += newOrderCopy.remains();
					asks_.insert(nodeHandle.value());
				}
				else
				{
					execute_(newOrderCopy, asksFront, asksFront.remains());
					newOrderCopy.filled += asksFront.remains();
					asks_.erase(asks_.begin());
				}
			}
			else
			{
				break;
			}
		}
		bids_.insert(newOrderCopy);
	}
	void Room::addAsk(const Ask& newOrder)
	{
		auto newOrderCopy = newOrder;
		while(newOrderCopy.remains() > 0 && !bids_.empty())
		{
			auto& bidsFront = *bids_.begin();
			if(newOrderCopy.px <= bidsFront.px)
			{
				if(bidsFront.remains() > newOrderCopy.remains())
				{
					execute_(bidsFront, newOrderCopy, newOrderCopy.remains());
					auto nodeHandle = bids_.extract(bids_.begin());
					nodeHandle.value().filled += newOrderCopy.remains();
					bids_.insert(nodeHandle.value());
				}
				else
				{
					execute_(bidsFront, newOrderCopy, bidsFront.remains());
					newOrderCopy.filled += bidsFront.remains();
					bids_.erase(bids_.begin());
				}
			}
			else
			{
				break;
			}
		}
		asks_.insert(newOrderCopy);
	}
	void Room::deleteBid(const OrderId& id)
	{
		std::erase_if(bids_, [&id](const auto& order){return order.id == id;});
	}
	void Room::deleteAsk(const OrderId& id)
	{
		std::erase_if(asks_, [&id](const auto& order){return order.id == id;});
	}
} // pex
