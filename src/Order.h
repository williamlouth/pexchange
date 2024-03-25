//
// Created by will on 24/03/24.
//

#pragma once
#include <cstdint>

#include "Decimal.h"
#include "Types.h"

namespace pex {


class Order {
public:
	OrderId id;
	TimePoint timeStamp;
	Decimal px;
	Decimal sz;
	Decimal filled;

	[[nodiscard]] Decimal remains() const;
};

class Bid : public Order
{
public:
	Bid(const OrderId& id, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);
	bool operator<(const Bid& other) const;
};

class Ask : public Order
{
public:
	Ask(const OrderId& id, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz);
	bool operator<(const Ask& other) const;
};

} // pex
