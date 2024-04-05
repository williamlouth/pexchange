//
// Created by will on 03/04/24.
//
#include <catch2/catch_test_macros.hpp>
#include "Dsl/IntegrationDsl.h"
#include <Room.h>
#include <Order.h>

namespace integration
{
	TEST_CASE("shouldLogonMultipleUsers", "[MultiUser]")
	{
		IntegrationDsl dsl;
		REQUIRE(dsl.createUser("will"));
		REQUIRE(dsl.createUser("bob"));
	}
	TEST_CASE("shouldAddOrder", "[MultiUser]")
	{
		IntegrationDsl dsl;
		dsl.addRoom("btc");
		dsl.createUser("will");
		dsl.createUser("bob");
		REQUIRE(dsl.createOrder("will", "btc", pex::Decimal{100}, pex::Decimal{10}) == "Successfully placed order: 0");
		REQUIRE(dsl.createOrder("bob", "btc", pex::Decimal{100}, pex::Decimal{10}) == "Successfully placed order: 0");
	}

	TEST_CASE("shouldMatchTwoUserOrders", "[MultiUser]")
	{
		IntegrationDsl dsl;
		dsl.addRoom("btc");
		dsl.createUser("will");
		dsl.createUser("bob");
		dsl.createOrder("will", "btc", pex::Decimal{100}, pex::Decimal{10});
		dsl.createOrder("bob", "btc", pex::Decimal{100}, pex::Decimal{-10});
		REQUIRE(dsl.userContainsFullFill("will", 0, pex::Decimal{10}));
		REQUIRE(dsl.userContainsFullFill("bob", 0, pex::Decimal{10}));
	}
}
