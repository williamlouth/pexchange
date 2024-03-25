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

	SECTION("bidFirst")
	{
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({1, {}, pex::Decimal{100}, pex::Decimal{10}});
	}
	SECTION("askFirst")
	{
		room.addAsk({1, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}});
	}

	REQUIRE(executed);
}

TEST_CASE("ShouldMatchFirstBidAndAsk", "[Room]")
{
	bool executed = false;
	pex::OrderId bidId{0};
	pex::OrderId askId{0};
	auto execute = [&executed,&bidId,&askId](const pex::Order& bid, const pex::Order& ask, pex::Decimal size)
	{
		executed = true;
		bidId = bid.id;
		askId = ask.id;
	};

	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({1, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({2, {}, pex::Decimal{90}, pex::Decimal{10}});
		room.addAsk({3, {}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(bidId == pex::OrderId{1});
	}
	SECTION("askFirst")
	{
		room.addAsk({1, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({2, {}, pex::Decimal{110}, pex::Decimal{10}});
		room.addBid({3, {}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(askId == pex::OrderId{1});
	}

	REQUIRE(executed);
}

TEST_CASE("ShouldNotMatchBidAndAsk", "[Room]")
{
	bool executed = false;
	auto execute = [&executed](const pex::Order& bid, const pex::Order& ask, pex::Decimal size){executed = true;};
	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({1, {}, pex::Decimal{110}, pex::Decimal{10}});
	}
	SECTION("askFirst")
	{
		room.addAsk({1, {}, pex::Decimal{110}, pex::Decimal{10}});
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}});
	}

	REQUIRE(!executed);
}

TEST_CASE("ShouldMatchBidAndAskInTimeOrder", "[Room]")
{
	bool executed = false;
	pex::OrderId bidId{0};
	pex::OrderId askId{0};
	auto execute = [&executed,&bidId,&askId](const pex::Order& bid, const pex::Order& ask, pex::Decimal size)
	{
		executed = true;
		bidId = bid.id;
		askId = ask.id;
	};
	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({1, pex::TimePoint{} + std::chrono::seconds{10}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({3, {}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(bidId == pex::OrderId{2});
	}
	SECTION("askFirst")
	{
		room.addAsk({1, pex::TimePoint{} + std::chrono::seconds{10}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({2, {}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({3, {}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(askId == pex::OrderId{2});
	}

	REQUIRE(executed);
}

TEST_CASE("ShouldMatchPartBidAndAsk", "[Room]")
{
	bool executed = false;
	pex::OrderId bidId{0};
	pex::OrderId askId{0};
	auto execute = [&executed,&bidId,&askId](const pex::Order& bid, const pex::Order& ask, pex::Decimal size)
	{
		executed = true;
	};
	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{100}});
		room.addAsk({3, {}, pex::Decimal{100}, pex::Decimal{10}});
	}
	SECTION("askFirst")
	{
		room.addAsk({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{100}});
		room.addBid({3, {}, pex::Decimal{100}, pex::Decimal{10}});
	}

	REQUIRE(executed);
}

TEST_CASE("ShouldMatch2BidAndAsk", "[Room]")
{
	int executed = 0;
	auto execute = [&executed](const pex::Order& bid, const pex::Order& ask, pex::Decimal size)
	{
		executed++;
	};
	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({2, pex::TimePoint{}, pex::Decimal{90}, pex::Decimal{10}});
		room.addAsk({3, {}, pex::Decimal{90}, pex::Decimal{20}});
		REQUIRE(executed == 2);
	}
	SECTION("askFirst")
	{
		room.addAsk({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({2, pex::TimePoint{}, pex::Decimal{110}, pex::Decimal{10}});
		room.addBid({3, {}, pex::Decimal{110}, pex::Decimal{20}});
		REQUIRE(executed == 2);
	}
}

TEST_CASE("ShouldMatchBidAndAskWithLeftOver", "[Room]")
{
	int executed = 0;
	auto execute = [&executed](const pex::Order& bid, const pex::Order& ask, pex::Decimal size)
	{
		executed++;
	};
	pex::Room room{execute};

	SECTION("bidFirst")
	{
		room.addBid({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		room.addAsk({2, {}, pex::Decimal{100}, pex::Decimal{20}});
		REQUIRE(executed == 1);
		room.addBid({3, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(executed == 2);
	}
	SECTION("askFirst")
	{
		room.addAsk({1, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		room.addBid({2, {}, pex::Decimal{100}, pex::Decimal{20}});
		REQUIRE(executed == 1);
		room.addAsk({3, pex::TimePoint{}, pex::Decimal{100}, pex::Decimal{10}});
		REQUIRE(executed == 2);
	}
}
