//
// Created by will on 24/03/24.
//

#include "Order.h"

namespace pex {
	Decimal Order::remains() const
	{
		return sz - filled;
	}
	Bid::Bid(const OrderId& id, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz)
		: Order{id, timeStamp, px, sz, Decimal{0}}
	{
	}

	bool Bid::operator<(const Bid& other) const
	{
		if(px == other.px)
		{
			return timeStamp < other.timeStamp;
		}
		return px > other.px;
	}

	Ask::Ask(const OrderId& id, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz)
		: Order{id, timeStamp, px, sz, Decimal{0}}
	{
	}

	bool Ask::operator<(const Ask& other) const
	{
		if(px == other.px)
		{
			return timeStamp < other.timeStamp;
		}
		return px < other.px;
	}
} // pex