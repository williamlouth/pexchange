//
// Created by will on 24/03/24.
//

#pragma once
#include <functional>
#include <set>

#include "Decimal.h"
#include "Types.h"

namespace pex {
	class Bid;
	class Ask;

	class Room {
    public:
		explicit Room(std::function<void(const Bid& bid, const Ask& ask, const Decimal& size)> execute);

		void addBid(const Bid& newOrder);
		void addAsk(const Ask& newOrder);
		void deleteBid(const OrderId& id);
		void deleteAsk(const OrderId& id);

    private:
        std::set<Bid> bids_;
        std::set<Ask> asks_;
		std::function<void(const Bid& bid, const Ask& ask, const Decimal& size)> execute_;
	};

} // pex
