//
// Created by will on 03/04/24.
//
#include <catch2/catch_test_macros.hpp>

#include "Dsl/AcceptanceDsl.h"

namespace acceptance
{

TEST_CASE("ShouldConnectAndLogin", "[Server]")
{
	AcceptanceDsl dsl;
	dsl.logOn();
	REQUIRE(dsl.waitForMessage("Logon successfull"));
}

}

