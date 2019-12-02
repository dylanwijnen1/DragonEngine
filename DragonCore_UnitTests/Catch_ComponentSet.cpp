#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Game/Components.h>

#include <Dragon/Generic/Math/MathDefinitions.h>
#include <Dragon/Generic/Serialization/OutStream.h>
#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Random.h>

struct TransformComponent
{
	TransformComponent() : m_position(0.f) {}
	TransformComponent(dragon::Vector2f pos) : m_position(pos) {}
	dragon::Vector2f m_position;
};


namespace dragon
{
	template<>
	inline TransformComponent InStream::Deserialize()
	{
		TransformComponent transform;
		transform.m_position = Deserialize<Vector2f>();
		return transform;
	}

	template<>
	inline void OutStream::Serialize(const TransformComponent& transform)
	{
		Serialize(transform.m_position);
	}
}

TEST_CASE("Testing Component Sets", "[DragonEngine][Game][Components]")
{
	dragon::ComponentSet<TransformComponent> components;

	SECTION("Reserving")
	{
		components.Reserve(1000);
	}

	SECTION("Add/Find/Remove")
	{
		dragon::Entity entity(0);

		// Add and find.
		{
			components.Add(entity);

			bool entityExists = components.Contains(entity);
			REQUIRE(entityExists);
		}

		// Remove and find
		{
			components.Remove(entity);

			bool entityExists = components.Contains(entity);
			REQUIRE(!entityExists);
		}
	}

	SECTION("Iterate")
	{
		constexpr size_t kCount = 100;
		for (size_t i = 0; i < kCount; ++i)
		{
			components.Add(i);
		}

		size_t total = 0;
		for (auto entity : components)
		{
			++total;
		}

		REQUIRE(total == 100);
	}

	SECTION("Serialize/Deserialize")
	{
		constexpr const char* kFileName = "transforms.bin";

		dragon::Vector2f pos{ 10.0f, 16.0f };

		// Add a Transform Component
		components.Emplace(0, pos);

		// Write to file
		{
			dragon::OutStream outStream(kFileName);
			components.Serialize(outStream);
		}

		// Clear components
		components.Clear();

		// Read from file
		dragon::InStream inStream(kFileName);
		components.Deserialize(inStream);

		// Get component to test.
		const auto& transform = components.GetComponent(0);
		REQUIRE(transform.m_position.x == pos.x);
		REQUIRE(transform.m_position.y == pos.y);
	}
}