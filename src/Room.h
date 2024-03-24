//
// Created by will on 24/03/24.
//

#pragma once
#include <functional>
#include <set>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	struct Order;

	class Room {
    public:
		explicit Room(const std::function<void(const Order& bid, const Order& ask, const Decimal& size)>& execute);

		void addBid(const Order& newOrder);
		void addAsk(const Order& newOrder);
		void deleteBid(const OrderId& id);
		void deleteAsk(const OrderId& id);

    private:
        std::set<Order> bids_;
        std::set<Order> asks_;
		std::function<void(const Order& bid, const Order& ask, const Decimal& size)> execute_;
	};

} // pex
