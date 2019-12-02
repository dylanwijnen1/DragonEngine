#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Generic/Handle.h>

TEMPLATE_TEST_CASE("Testing Handles", "[DragonEngine][Generic][Handle]", uint8_t, uint16_t, uint32_t, uint64_t)
{
	using TestHandle = dragon::Handle<TestType>;

	SECTION("Construction")
	{

		SECTION("From Constructor")
		{
			TestHandle handle(10);
			REQUIRE(handle.GetId() == (TestType)10);
		}

		SECTION("From Literal")
		{
			TestHandle handle = (TestType)15;
			REQUIRE(handle.GetId() == (TestType)15);
		}

		SECTION("Versioning")
		{
			TestHandle handle = (TestType)15;

			REQUIRE(handle.GetVersion() == 0);
			handle.Increment();
			REQUIRE(handle.GetVersion() == 1);
		}

		SECTION("Validating")
		{
			TestHandle validHandle = (TestType)15;
			TestHandle invalidHandle(TestHandle::Invalid);

			REQUIRE(validHandle.IsValid());
			REQUIRE(!invalidHandle.IsValid());

			validHandle.Invalidate();
			invalidHandle.SetVersion(0);
			REQUIRE(invalidHandle.IsValid());
			REQUIRE(!validHandle.IsValid());

		}
	}

}