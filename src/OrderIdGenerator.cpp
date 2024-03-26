//
// Created by will on 26/03/24.
//

#include "OrderIdGenerator.h"

namespace pex {
	OrderIdGenerator::OrderIdGenerator(const OrderId& lastOrderId)
		: lastOrderId_{lastOrderId}
	{
	}
	OrderId OrderIdGenerator::getNextOrderId()
	{
		return ++lastOrderId_;
	}
} // pex