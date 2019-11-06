#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Generic/DirectedGraph.h>

TEST_CASE("Testing Graph", "[DragonEngine][Generic][Graph]")
{

	SECTION("Simple Data")
	{
		dragon::DirectedGraph<int> graph;
		SECTION("Adding vertices")
		{
			auto handle = graph.Add(100);
			REQUIRE(graph[handle].m_data == 100);
		}
	}

	struct Complex
	{
		eastl::string firstname;
		eastl::string lastname;
	};

	SECTION("Complex Data")
	{
		dragon::DirectedGraph<Complex> graph;
		SECTION("Adding vertices")
		{
			auto handle = graph.Emplace("Dylan", "Wijnen");
			REQUIRE(graph[handle].m_data.firstname.compare("Dylan") == 0); // Note: Can't do firstname == "Dylan" because of begin/end operators ambigous calls.
			REQUIRE(graph[handle].m_data.lastname.compare("Wijnen") == 0);

			auto handle2 = graph.Emplace("Dragon", "Engine");
			REQUIRE(graph[handle2].m_data.firstname.compare("Dragon") == 0); // Note: See above.
			REQUIRE(graph[handle2].m_data.lastname.compare("Engine") == 0);
		}
	}


}