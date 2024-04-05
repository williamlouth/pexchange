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
		dsl.createUser("will");
		dsl.createUser("bob");
	}
}
