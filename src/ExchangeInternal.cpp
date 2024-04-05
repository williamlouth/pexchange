//
// Created by will on 03/04/24.
//

#include "ExchangeInternal.h"
#include <Room.h>
#include <Order.h>

namespace pex {
	ExchangeInternal::ExchangeInternal()
		: userManager_{
			[this](const RoomId& roomId, const Bid& bid) { this->addBid(roomId, bid); },
			[this](const RoomId& roomId, const Ask& ask) { this->addAsk(roomId, ask); },
			[this](const RoomId& roomId, const OrderId& id) { this->deleteBid(roomId, id); },
			[this](const RoomId& roomId, const OrderId& id) { this->deleteAsk(roomId, id); },
			[this](const UserId& user, const ClOrdId& clOrdId, const Decimal& fillAmount) { this->fullyFilled(user, clOrdId, fillAmount); },
			[this](const UserId& user, const ClOrdId& clOrdId, const Decimal& fillAmount) { this->partiallyFilled(user, clOrdId, fillAmount); },
		  }
		  , messageParser_{
			  [this](const auto& userId, const auto& nos) { return newOrderSingle(userId, nos); },
			  [this](const auto& userId, const auto& can) { return cancelOrder(userId, can); },
			  [this](const auto& connection, const auto& message) { return sendMessage(connection, message); }
		  }
	{
	}
	void ExchangeInternal::addRoom(const RoomId& roomId)
	{
		rooms_.insert({roomId, Room{[this](const Bid& bid, const Ask& ask, const Decimal& size){this->execute(bid, ask, size);}}} );
	}
	void ExchangeInternal::execute(const Bid& bid, const Ask& ask, const Decimal& fillAmount)
	{
		userManager_.executeBid(bid, fillAmount);
		userManager_.executeAsk(ask, fillAmount);
	}
	void ExchangeInternal::addBid(const RoomId& roomId, const Bid& bid)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.addBid(bid);
		}
	}
	void ExchangeInternal::addAsk(const RoomId& roomId, const Ask& ask)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.addAsk(ask);
		}
	}
	void ExchangeInternal::deleteBid(const RoomId& roomId, const OrderId& id)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.deleteBid(id);
		}
	}
	void ExchangeInternal::deleteAsk(const RoomId& roomId, const OrderId& id)
	{
		if(auto itr = rooms_.find(roomId); itr != rooms_.end())
		{
			itr->second.deleteAsk(id);
		}
	}
	void ExchangeInternal::partiallyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)
	{
		messageParser_.partiallyFilled(user, clOrdId, filledAmount);
	}
	void ExchangeInternal::fullyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)
	{
		messageParser_.fullyFilled(user, clOrdId, filledAmount);
	}
	std::string ExchangeInternal::newOrderSingle(const UserId& user, const NewOrderSingle& newOrderSingle)
	{
		return userManager_.newOrderSingle(user, newOrderSingle);
	}
	std::string ExchangeInternal::cancelOrder(const UserId& user, const CancelOrder& cancelOrder)
	{
		return userManager_.cancelOrder(user, cancelOrder);
	}
} // pex