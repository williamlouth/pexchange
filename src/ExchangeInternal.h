//
// Created by will on 03/04/24.
//

#pragma once
#include <map>
#include <MessageParser.h>
#include <UserManager.h>
#include <nlohmann/json_fwd.hpp>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;
	class Room;


class ExchangeInternal {
    public:
		ExchangeInternal();

		void addRoom(const RoomId& roomId);
    protected:
		void execute(const Bid& bid, const Ask& ask, const Decimal& size);
		void addBid(const RoomId& roomId, const Bid& bid);
		void addAsk(const RoomId& roomId, const Ask& ask);
		void deleteBid(const RoomId& roomId, const OrderId& id);
		void deleteAsk(const RoomId& roomId, const OrderId& id);

		void partiallyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount);
		void fullyFilled(const UserId& user, const ClOrdId& clOrdId, const Decimal& filledAmount);

		std::string newOrderSingle(const UserId& user, const NewOrderSingle& newOrderSingle);
		std::string cancelOrder(const UserId& user, const CancelOrder& cancelOrder);

        std::map<RoomId,Room> rooms_;
		UserManager userManager_;
		MessageParser messageParser_;
};

} // pex
