//
// Created by will on 26/03/24.
//

#pragma once
#include <Order.h>

namespace pex {

class UserOrder : public Order{
    public:
    explicit UserOrder(const OrderId& id, const TimePoint& timeStamp, const Decimal& px, const Decimal& sz, const RoomId& roomId);

    RoomId roomId;
};

} // pex
