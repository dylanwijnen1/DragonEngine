#pragma once


#include <Dragon/Generic/Math/MathFunctions.h>

#include <Game/Tilemap.h>
#include <Game/Vector2.h>

#include <EASTL/priority_queue.h>
#include <EASTL/hash_map.h>
#include <EASTL/array.h>

#include <queue>

enum struct PathPlanStatus
{
	kFinished,
	kProcessing,
	kFailed,
};

struct TilePathData
{
	float m_weight;
	bool m_isNavigable;

	TilePathData()
		: m_weight(1.0f)
		, m_isNavigable(true)
	{}
};

struct PathNode;

namespace _internal
{
	bool PriorityFunc(PathNode* pLeft, PathNode* pRight);
}

class PathPlan
{
	inline static constexpr size_t kNeighborhoodCount = 8;
	using Neighborhood = eastl::array<size_t, kNeighborhoodCount>;

	using OpenSet = eastl::priority_queue<PathNode*, eastl::vector<PathNode*>, decltype(&_internal::PriorityFunc)>;
	OpenSet m_openSet;

	using PathNodes = eastl::hash_map<size_t, PathNode*>;
	PathNodes m_nodes;

	using PathingData = eastl::hash_map<TileID, TilePathData>;
	PathingData m_pathingData;
	TilePathData m_defaultTilePathData;

	const Tilemap* m_pTilemap;

	size_t m_goalIndex;

	PathPlanStatus m_status;

public:

	PathPlan()
		: m_pTilemap(nullptr)
		, m_openSet(&_internal::PriorityFunc)
		, m_goalIndex(Tilemap::kInvalidTileIndex)
		, m_status(PathPlanStatus::kFailed)
		, m_defaultTilePathData()
	{}

	bool Init(Vector2 start, Vector2 goal, const Tilemap* pTilemap);
	bool Init(size_t start, size_t goal, const Tilemap* pTilemap);

	void Update();

	PathPlanStatus GetStatus() const { return m_status; }

	void Draw(sf::RenderTarget* pTarget) const;

	Vector2 GetNodePosition();
	bool Next();

	// Tile Pathing Data
	const TilePathData& GetTilePathData(TileID id) const;
	TilePathData& GetTilePathData(TileID id);

private:

	void SetStatus(PathPlanStatus status) { m_status = status; }

	PathNode* FindPathNode(size_t tileIndex) const;
	PathNode* CreatePathNode(size_t tileIndex);
	void AddToOpenSet(PathNode* pNode);
	void UpdateNodePriority(PathNode* pNode);

	void GetNeighbors(Vector2 currentNodePos, Neighborhood& neighborhood) const;

	float AverageWeight(const PathNode* pFrom, const PathNode* pTo) const;
	float DistanceToGoal(const PathNode* pFrom) const;
};