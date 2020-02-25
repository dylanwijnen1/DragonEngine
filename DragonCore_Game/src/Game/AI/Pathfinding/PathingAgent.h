#pragma once

#include <Game/AI/Pathfinding/PathPlan.h>
#include <Game/AI/KinematicAgent.h>

#include <chrono>

class PathingAgent : public KinematicAgent
{
	PathPlan m_pathPlan;
	const Tilemap* m_pTilemap;
	class Path* m_pPath;

	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<Clock, Clock::duration>;
	using Duration = std::chrono::duration<double>;

	TimePoint m_startTime;
	TimePoint m_endTime;

public:

	PathingAgent()
		: m_pathPlan()
		, m_pTilemap(nullptr)
		, m_pPath(nullptr)
	{}
	
	bool Init(const Tilemap* pTilemap);

	void PathFindTo(Vector2 pos);

	virtual void Update(float dt) override;

	void Draw(sf::RenderTarget* pTarget);
};