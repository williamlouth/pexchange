//
// Created by will on 24/03/24.
//

#pragma once
#include <cstdint>

#include "Decimal.h"
#include "Types.h"

namespace pex {


struct Order {
	OrderId id;
	TimePoint timeStamp;
	Decimal px;
	Decimal sz;
	Decimal filled;
	bool isBid;

	Decimal remains() const;

	bool operator<(const Order& other) const;

};

} // pex
