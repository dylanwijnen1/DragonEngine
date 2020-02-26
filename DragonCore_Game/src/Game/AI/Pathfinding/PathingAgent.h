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

	class WanderBehavior* m_pWanderBehavior;
	class FollowPathBehavior* m_pFollowPathBehavior;
	class StruggleBehavior* m_pStruggleBehavior;
	class Behavior* m_pBehavior;

public:

	PathingAgent()
		: m_pathPlan()
		, m_pTilemap(nullptr)
		, m_pPath(nullptr)
		, m_pWanderBehavior(nullptr)
		, m_pFollowPathBehavior(nullptr)
		, m_pStruggleBehavior(nullptr)
		, m_pBehavior(nullptr)
	{}
	
	bool Init(const Tilemap* pTilemap);

	virtual void Update(float dt) override;

	void Draw(sf::RenderTarget* pTarget);

	void PathFindTo(Vector2 pos);

	void TransitionToBehavior(Behavior* pBehavior);

	Path* GetPath() { return m_pPath; }
	const Path* GetPath() const { return m_pPath; }

	const Tilemap* GetTilemap() const { return m_pTilemap; }

};