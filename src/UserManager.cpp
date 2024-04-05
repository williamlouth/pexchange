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
	void UserManager::executeBid(const Bid& bid, const Decimal& fillAmount)
	{
		if(const auto user = users_.find(bid.user); user != users_.end())
		{
			user->second.executeBid(bid, fillAmount);
		}
	}
	void UserManager::executeAsk(const Ask& ask, const Decimal& fillAmount)
	{
		if(const auto user = users_.find(ask.user); user != users_.end())
		{
			user->second.executeAsk(ask, fillAmount);
		}
	}
	void UserManager::addUser(const UserId& user)
	{
		users_.insert(std::make_pair(user,User{orderIdGenerator_, addBid_, addAsk_, deleteBid_, deleteAsk_, fullyFilled_, partiallyFilled_}));
	}
} // pex