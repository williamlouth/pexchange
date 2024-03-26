//
// Created by will on 26/03/24.
//

#pragma once
#include "Types.h"

namespace pex {

class OrderIdGenerator {
public:
    OrderIdGenerator(const OrderId& lastOrderId);
    [[nodiscard]] OrderId getNextOrderId();

private:

    OrderId lastOrderId_;

};

} // pex
