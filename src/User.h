//
// Created by will on 26/03/24.
//

#pragma once
#include <functional>
#include <map>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;

    class User {
    public:
	    User(const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid, const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk);

	    void addOrder(const ClOrdId& clOrdId, const RoomId& roomId, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);
    private:
		void createOrder(const ClOrdId& clOrdId, const RoomId& roomId, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);


		std::function<void(const RoomId& roomId, const Bid& bid)> addBid_;
		std::function<void(const RoomId& roomId, const Ask& ask)> addAsk_;
        std::map<ClOrdId,Bid> bids_;
        std::map<ClOrdId,Ask> asks_;
};

} // pex
