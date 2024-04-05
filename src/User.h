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
	struct NewOrderSingle;
	struct CancelOrder;
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
	         const std::function<void(const RoomId& roomId, const OrderId& id)>& deleteAsk,
	         const std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)>& fullyFilled,
	         const std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)>& partiallyFilled
	    );

	    std::string addOrder(const NewOrderSingle& newOrderSingle);
	    std::string deleteOrder(const CancelOrder& cancelOrder);
    	void executeBid(const Bid& bid, const Decimal& fillAmount);
    	void executeAsk(const Ask& ask, const Decimal& fillAmount);
    private:
		void createOrder(const NewOrderSingle& newOrderSingle);


		std::function<void(const RoomId& roomId, const Bid& bid)> addBid_;
		std::function<void(const RoomId& roomId, const Ask& ask)> addAsk_;
	    std::function<void(const RoomId& roomId, const OrderId& id)> deleteBid_;
	    std::function<void(const RoomId& roomId, const OrderId& id)> deleteAsk_;

		std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)> fullyFilled_;
		std::function<void(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount)> partiallyFilled_;

        std::map<ClOrdId,UserOrder> bids_;
        std::map<ClOrdId,UserOrder> asks_;
    	OrderIdGenerator& orderIdGenerator_;
};

} // pex
