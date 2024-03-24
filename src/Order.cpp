//
// Created by will on 24/03/24.
//

#include "Order.h"

namespace pex {
	Decimal Order::remains() const
	{
		return sz - filled;
	}
	bool Order::operator<(const Order& other) const
	{
		if(px == other.px)
		{
			return timeStamp < other.timeStamp;
		}
		return (px > other.px) * isBid;
	}
} // pex