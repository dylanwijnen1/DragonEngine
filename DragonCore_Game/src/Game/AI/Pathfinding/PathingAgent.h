#pragma once

#include <Game/AI/Pathfinding/PathPlan.h>
#include <Game/AI/KinematicAgent.h>

class PathingAgent : public KinematicAgent
{
	PathPlan m_pathPlan;

public:
	virtual void Update(float dt) override;

	void Draw(sf::RenderTarget* pTarget);
};