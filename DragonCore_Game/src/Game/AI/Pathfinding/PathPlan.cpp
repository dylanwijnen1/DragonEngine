#include "PathPlan.h"

#include <Game/AI/Pathfinding/PathNode.h>
#include <Game/AI/Pathfinding/Path.h>

#include <Dragon/Debug.h>

#include <SFML/Graphics.hpp>

#include <assert.h>

bool PathPlan::Init(Vector2 start, Vector2 goal, const Tilemap* pTilemap)
{
	return Init(pTilemap->GetTileIndex(start), pTilemap->GetTileIndex(goal), pTilemap);
}

bool PathPlan::Init(size_t start, size_t goal, const Tilemap* pTilemap)
{
	m_pTilemap = pTilemap;

	m_openSet.get_container().clear();

	for (auto& pair : m_nodes)
	{
		delete pair.second;
	}
	m_nodes.clear();

	m_goalIndex = goal;
	PathNode* pNode = CreatePathNode(start);
	pNode->m_gScore = 0.f;
	pNode->m_fScore = DistanceToGoal(pNode);

	AddToOpenSet(pNode);

	SetStatus(PathPlanStatus::kProcessing);

	return true;
}

void PathPlan::Update()
{
	if (m_status != PathPlanStatus::kProcessing)
	{
		return;
	}

	if (m_openSet.empty())
	{
		m_onFinished(nullptr);
		DLOG("Finished, Expanded: %i", m_nodes.size());
		SetStatus(PathPlanStatus::kFailed);
		return;
	}

	PathNode* pCurrent = m_openSet.top();

	if (pCurrent->m_tileIndex == m_goalIndex)
	{
		Path* pPath = new Path();
		ConstructPath(pPath);
		m_onFinished(pPath);

		DLOG("Finished, Expanded: %i", m_nodes.size());
		SetStatus(PathPlanStatus::kFinished);

		return;
	}

	m_openSet.pop();

	pCurrent->Close();

	//DLOG("Expanding: (%i, %i), fScore: %f, gScore: %f", pCurrent->m_tilePos.x, pCurrent->m_tilePos.y, pCurrent->m_fScore, pCurrent->m_gScore);

	Neighborhood neighborhood;
	neighborhood.fill(Tilemap::kInvalidTileIndex); // equal to std::memset
	GetNeighbors(pCurrent->m_tilePos, neighborhood);

	for (size_t neighborIndex : neighborhood)
	{
		if (neighborIndex != Tilemap::kInvalidTileIndex)
		{
			PathNode* pNeighbor = FindPathNode(neighborIndex);
			
			// Already expanded
			if (pNeighbor && pNeighbor->IsClosed())
				continue;

			if(pNeighbor == nullptr)
				pNeighbor = CreatePathNode(neighborIndex);

			// Get score from current through this node.
			const float gScoreTemp = pCurrent->m_gScore + AverageWeight(pCurrent, pNeighbor);

			if (gScoreTemp < pNeighbor->m_gScore)
			{
				pNeighbor->m_pPrevious = pCurrent;
				pNeighbor->m_gScore = gScoreTemp;
				pNeighbor->m_fScore = gScoreTemp + std::sqrt(DistanceToGoal(pNeighbor)); // + Hueristic

				AddToOpenSet(pNeighbor);
				UpdateNodePriority(pNeighbor);
			}
		}
	}
}

void PathPlan::Draw(sf::RenderTarget* pTarget) const
{
	sf::VertexArray expandedNodes(sf::PrimitiveType::Quads, m_nodes.size() * 4);
	for (auto& pair : m_nodes)
	{
		PathNode* pNode = pair.second;
		sf::Color color = sf::Color::Cyan;
		if (pNode->IsClosed())
			color = sf::Color::Black;

		Vector2 pos = pNode->m_tilePos * 16;
		pos.x += 4;
		pos.y += 4;

		auto topLeft = sf::Vector2f((float)pos.x, (float)pos.y); // Top Left
		auto topRight = sf::Vector2f(((float)pos.x + 8), (float)pos.y); // Top Right
		auto bottomRight = sf::Vector2f(((float)pos.x + 8), ((float)pos.y + 8)); // Bottom Right
		auto bottomLeft = sf::Vector2f((float)pos.x, ((float)pos.y + 8)); // Bottom Left

		expandedNodes.append(sf::Vertex(bottomLeft, color));
		expandedNodes.append(sf::Vertex(topLeft, color));
		expandedNodes.append(sf::Vertex(topRight, color));
		expandedNodes.append(sf::Vertex(bottomRight, color));
	}

	pTarget->draw(expandedNodes);
}

void PathPlan::ConstructPath(Path* path)
{
	path->Clear();

	// Reconstruct path.
	PathNode* pCurrent = m_nodes[m_goalIndex];
	while (pCurrent->m_pPrevious != nullptr)
	{
		path->PushWaypoint(pCurrent->m_tilePos);
		pCurrent = pCurrent->m_pPrevious;
	}

	path->Reverse();
}

const TilePathData& PathPlan::GetTilePathData(TileID id) const
{
	auto result = m_pathingData.find(id);
	if (result != m_pathingData.end())
		return result->second;

	return m_defaultTilePathData;
}

TilePathData& PathPlan::GetTilePathData(TileID id)
{
	return m_pathingData[id];
}

PathNode* PathPlan::FindPathNode(size_t tileIndex) const
{
	if (auto result = m_nodes.find(tileIndex); result != m_nodes.end())
	{
		return result->second;
	}

	return nullptr;
}

PathNode* PathPlan::CreatePathNode(size_t tileIndex)
{
	// TODO: Pool PathNodes.
	auto result = m_nodes.emplace(tileIndex, new PathNode(tileIndex, m_pTilemap->GetTilePosition(tileIndex)));
	return result.first->second;
}

void PathPlan::AddToOpenSet(PathNode* pNode)
{
	assert(pNode != nullptr);
	m_openSet.emplace(pNode);
}

void PathPlan::UpdateNodePriority(PathNode* pNode)
{
	auto& container = m_openSet.get_container();
	for (size_t i = 0; i < container.size(); ++i)
	{
		if (container.at(i) == pNode)
		{
			m_openSet.change(i);
			return;
		}
	}
}

void PathPlan::GetNeighbors(Vector2 pos, Neighborhood& neighborhood) const
{
	auto addIfNavigable = [this](int x, int y) -> size_t
	{
		TileID tileId = m_pTilemap->GetTile(x, y);

		if (tileId == Tilemap::kInvalidTileID)
			return Tilemap::kInvalidTileIndex;

		auto& data = GetTilePathData(tileId);
		if (data.m_isNavigable)
		{
			size_t index = m_pTilemap->GetTileIndex(x, y);
			Vector2 pos = m_pTilemap->GetTilePosition(index);
			//DLOG("Given: (%i, %i) Index: %i, Pos: (%i, %i)", x, y, index, pos.x, pos.y);
			return index;
		}

		return Tilemap::kInvalidTileIndex;
	};

	auto allowDiagonal = [](size_t hor, size_t vert) -> bool
	{
		return hor != Tilemap::kInvalidTileIndex && vert != Tilemap::kInvalidTileIndex;
	};

	neighborhood[0] = addIfNavigable(pos.x, pos.y - 1); // North
	neighborhood[1] = addIfNavigable(pos.x + 1, pos.y); // East
	neighborhood[2] = addIfNavigable(pos.x, pos.y + 1); // South
	neighborhood[3] = addIfNavigable(pos.x - 1, pos.y); // West

	if(allowDiagonal(neighborhood[0], neighborhood[1]))
		neighborhood[4] = addIfNavigable(pos.x + 1, pos.y - 1); // North East
	if(allowDiagonal(neighborhood[2], neighborhood[3]))
		neighborhood[5] = addIfNavigable(pos.x + 1, pos.y + 1); // South East
	if(allowDiagonal(neighborhood[2], neighborhood[3]))
		neighborhood[6] = addIfNavigable(pos.x - 1, pos.y + 1); // South West
	if(allowDiagonal(neighborhood[0], neighborhood[3]))
		neighborhood[7] = addIfNavigable(pos.x - 1, pos.y - 1); // North West
}

float PathPlan::AverageWeight(const PathNode* pFrom, const PathNode* pTo) const
{
	float fromWeight = GetTilePathData(m_pTilemap->GetTile(pFrom->m_tileIndex)).m_weight;
	float toWeight = GetTilePathData(m_pTilemap->GetTile(pTo->m_tileIndex)).m_weight;
	return (fromWeight + toWeight) / 2.0f;
}

float PathPlan::DistanceToGoal(const PathNode* pFrom) const
{
	Vector2 goalPos = m_pTilemap->GetTilePosition(m_goalIndex);
	return (float)pFrom->m_tilePos.DistanceSqrd(goalPos);
}

bool _internal::PriorityFunc(PathNode* pLeft, PathNode* pRight)
{
	return pLeft->m_fScore > pRight->m_fScore;
}
