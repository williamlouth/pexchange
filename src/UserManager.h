//
// Created by will on 26/03/24.
//

#pragma once
#include <functional>
#include <map>
#include <OrderIdGenerator.h>
#include <User.h>
#include <UserOrder.h>

#include "Types.h"

namespace pex {
	class Bid;
	class Ask;

    class UserManager {
    public:
	    UserManager(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
	                const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk,
					const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteBid,
	                const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk );

    private:

		std::function<void(const RoomId& roomId, const Bid& bid)> addBid_;
		std::function<void(const RoomId& roomId, const Ask& ask)> addAsk_;
		std::function<void(const RoomId& roomId, const OrderId& id)> deleteBid_;
		std::function<void(const RoomId& roomId, const OrderId& id)> deleteAsk_;
    	std::map<UserId, User> users_;

    	OrderIdGenerator orderIdGenerator_;

};

} // pex
