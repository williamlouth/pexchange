//
// Created by will on 28/03/24.
//

#pragma once
#include "Decimal.h"
#include "Types.h"

namespace pex {

struct NewOrderSingle {
    ClOrdId clOrdId;
    RoomId roomId;
    TimePoint timeStamp;
    Decimal px;
    Decimal sz;
};

} // pex
