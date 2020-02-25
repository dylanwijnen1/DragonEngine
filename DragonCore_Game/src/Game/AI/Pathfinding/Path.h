#pragma once

#include <Game/Vector2.h>
#include <EASTL/vector.h>
#include <SFML/Graphics/VertexArray.hpp>

namespace sf
{
	class RenderTarget;
}

class Path
{
	using Waypoints = eastl::vector<Vector2>;
	Waypoints m_waypoints;

	sf::VertexArray m_vertices;

public:

	Path()
		: m_waypoints()
		, m_vertices(sf::PrimitiveType::LineStrip)
	{}

	void Draw(sf::RenderTarget* pTarget);

	void PushWaypoint(Vector2 pos);
	void Reverse() { eastl::reverse(m_waypoints.begin(), m_waypoints.end()); }
	void Clear() { m_waypoints.clear(); };
};