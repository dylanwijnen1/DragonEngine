#pragma once

#include <Dragon/Generic/Math/MathFunctions.h>
#include <Game/Tilemap.h>
#include <Game/Vector2.h>

#include <EASTL/functional.h>

struct PathNode
{
	size_t m_tileIndex;
	Vector2 m_tilePos;

	float m_gScore;
	float m_fScore;

	bool m_closed;

	PathNode* m_pPrevious;

	PathNode()
		: PathNode(Tilemap::kInvalidTileIndex, Vector2())
	{}

	PathNode(size_t tileIndex, Vector2 tilePos)
		: m_tileIndex(tileIndex)
		, m_tilePos(tilePos)
		, m_gScore(dragon::math::kInfinity)
		, m_fScore(dragon::math::kInfinity)
		, m_closed(false)
		, m_pPrevious(nullptr)
	{}

	bool IsClosed() const { return m_closed; }
	void Close() { m_closed = true; }
};