//
// Created by will on 26/03/24.
//

#include "UserManager.h"
#include "User.h"
#include "Order.h"

namespace pex {
	UserManager::UserManager(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
		const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk)
			: addBid_{addBid}
			, addAsk_{addAsk}
	{
	}
} // pex