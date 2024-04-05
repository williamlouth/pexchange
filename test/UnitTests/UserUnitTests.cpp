//
// Created by will on 26/03/24.
//
#include <Messages/CancelOrder.h>
#include <Messages/NewOrderSingle.h>
#include <OrderIdGenerator.h>
#include <User.h>
#include <UserOrder.h>
#include <catch2/catch_test_macros.hpp>

#include "Types.h"

namespace pex
{
	class Ask;
	class Bid;
}

auto emptyAddBid = [](const pex::RoomId&, const pex::Bid&){};
auto emptyAddAsk = [](const pex::RoomId&, const pex::Ask&){};
auto emptyDelete = [](const pex::RoomId&, const pex::OrderId&){};
auto emptyFilled = [](const pex::UserId&, const pex::ClOrdId&, const pex::Decimal&){};

TEST_CASE("ShouldAddBidAsk", "[Room]")
{
	auto orderIdGen = pex::OrderIdGenerator{0};
	bool addedBid = false;
	bool addedAsk = false;
	auto addBid = [&addedBid](const pex::RoomId&, const pex::Bid& bid){addedBid = true; REQUIRE(bid.id == 1);};
	auto addAsk = [&addedAsk](const pex::RoomId&, const pex::Ask& ask){addedAsk = true; REQUIRE(ask.id == 2);};

	pex::User u{orderIdGen, addBid, addAsk, emptyDelete, emptyDelete, emptyFilled, emptyFilled};
	u.addOrder(pex::NewOrderSingle{"user", pex::ClOrdId{0}, pex::RoomId{"roomy"}, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
	REQUIRE(addedBid);
	u.addOrder(pex::NewOrderSingle{"user", 1, "roomy", {}, pex::Decimal{110}, pex::Decimal{-10}});
	REQUIRE(addedAsk);
}

TEST_CASE("ShouldDeleteBidAsk", "[Room]")
{
	auto orderIdGen = pex::OrderIdGenerator{0};
	bool deletedBid = false;
	bool deletedAsk = false;
	auto deleteBid = [&deletedBid](const pex::RoomId&, const pex::OrderId& id){deletedBid = true; REQUIRE(id == 1);};
	auto deleteAsk = [&deletedAsk](const pex::RoomId&, const pex::OrderId& id){deletedAsk = true; REQUIRE(id == 2);};

	pex::User u{orderIdGen, emptyAddBid, emptyAddAsk, deleteBid, deleteAsk, emptyFilled, emptyFilled};
	u.addOrder(pex::NewOrderSingle{"user", 0, "roomy", {}, pex::Decimal{100}, pex::Decimal{10}});
	u.addOrder(pex::NewOrderSingle{"user", 1, "roomy", {}, pex::Decimal{110}, pex::Decimal{-10}});
	u.deleteOrder(pex::CancelOrder{0});
	REQUIRE(deletedBid);
	u.deleteOrder(pex::CancelOrder{1});
	REQUIRE(deletedAsk);
}