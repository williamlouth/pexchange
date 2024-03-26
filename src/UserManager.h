//
// Created by will on 26/03/24.
//

#pragma once
#include <functional>
#include <map>
#include <User.h>

#include "Types.h"

namespace pex {
	class Bid;
	class Ask;

    class UserManager {
    public:
	    UserManager(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
		    const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk);

    private:

		std::function<void(const RoomId& roomId, const Bid& bid)> addBid_;
		std::function<void(const RoomId& roomId, const Ask& ask)> addAsk_;
    	std::map<UserId, User> users_;

};

} // pex
