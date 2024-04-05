//
// Created by will on 26/03/24.
//

#include "UserOrder.h"

namespace pex {
	UserOrder::UserOrder(const OrderId& id,
		const UserId& user,
		const TimePoint& timeStamp,
		const Decimal& px,
		const Decimal& sz,
		const RoomId& roomId)
			: Order{id, user, timeStamp, px, sz, Decimal{0}}
			, roomId{roomId}
	{
	}
} // pex