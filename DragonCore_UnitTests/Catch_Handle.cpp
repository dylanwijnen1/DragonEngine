#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Generic/Handle.h>

TEST_CASE("Testing Handles", "[DragonEngine][Generic][Handle]")
{
	SECTION("From Integral")
	{
		dragon::Handle handle = 1234;
		REQUIRE(handle.GetId() == 1234);

		SECTION("Versioning")
		{
			REQUIRE(handle.GetVersion() == 0);
			handle.Increment();
			REQUIRE(handle.GetVersion() == 1);
			handle.Increment();
			REQUIRE(handle.GetVersion() == 2);
		}
	}
}