//
// Created by will on 26/03/24.
//

#pragma once
#include <functional>
#include <map>

#include "Decimal.h"
#include "Types.h"

namespace pex
{
	class OrderIdGenerator;
}

namespace pex {
	class Bid;
	class Ask;
	class UserOrder;

    class User {
    public:
	    User(OrderIdGenerator& orderIdGenerator,
	         const std::function<void(const RoomId& roomId, const Bid& bid)>& addBid,
	         const std::function<void(const RoomId& roomId, const Ask& ask)>& addAsk,
	         const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteBid,
	         const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk
	    );

	    void addOrder(const ClOrdId& clOrdId, const RoomId& roomId, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);
	    void deleteOrder(const ClOrdId& clOrdId);
    private:
		void createOrder(const ClOrdId& clOrdId, const RoomId& roomId, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);


		std::function<void(const RoomId& roomId, const Bid& bid)> addBid_;
		std::function<void(const RoomId& roomId, const Ask& ask)> addAsk_;
	    std::function<void(const RoomId& roomId, const OrderId& id)> deleteBid_;
	    std::function<void(const RoomId& roomId, const OrderId& id)> deleteAsk_;

        std::map<ClOrdId,UserOrder> bids_;
        std::map<ClOrdId,UserOrder> asks_;
    	OrderIdGenerator& orderIdGenerator_;
};

} // pex
