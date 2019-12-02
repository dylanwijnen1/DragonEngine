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

TEST_CASE("Testing Component Sets", "[DragonEngine][Game][Components]")
{

}