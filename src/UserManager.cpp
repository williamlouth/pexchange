//
// Created by will on 26/03/24.
//

#include "UserManager.h"
#include "User.h"
#include "Order.h"

namespace pex
{
	UserManager::UserManager(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
	                         const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk,
	                         const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteBid,
	                         const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk)
		: addBid_{addBid}
		, addAsk_{addAsk}
		, deleteBid_{deleteBid}
		, deleteAsk_{deleteAsk}
		, orderIdGenerator_{OrderId{0}} //TODO: load last value from database
	{
	}
	std::string UserManager::newOrderSingle(const UserId& userId, const NewOrderSingle& newOrderSingle)
	{
		if(const auto user = users_.find(userId); user == users_.end())
		{
			return "Invalid User";
		}
		else
		{
			return user->second.addOrder(newOrderSingle);
		}
	}
	std::string UserManager::cancelOrder(const UserId& userId, const CancelOrder& cancelOrder)
	{
		if(const auto user = users_.find(userId); user == users_.end())
		{
			return "Invalid User";
		}
		else
		{
			return user->second.deleteOrder(cancelOrder);
		}
	}
} // pex