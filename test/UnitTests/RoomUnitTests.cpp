//
// Created by will on 24/03/24.
//
#include <catch2/catch_test_macros.hpp>

#include <Room.h>
#include <Order.h>


TEST_CASE("ShouldMatchBidAndAsk", "[Room]")
{
	bool executed = false;
	auto execute = [&executed](const pex::Order& bid, const pex::Order& ask, pex::Decimal size){executed = true;};
	pex::Room room{execute};

	room.addAsk({1, {}, pex::Decimal{100}, pex::Decimal{10}, pex::Decimal{0}, false});
	room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}, pex::Decimal{0}, true});
	REQUIRE(executed);
}