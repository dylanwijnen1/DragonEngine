#include "FollowPathBehavior.h"

#include <Game/AI/Pathfinding/PathingAgent.h>
#include <Game/AI/Pathfinding/Path.h>

#include <Dragon/Debug.h>

Behavior* FollowPathBehavior::Update(float dt)
{
	KinematicAgent* pAgent = GetAgent();

	if (!pAgent)
	{
		DWARN_TRACE("Agent is nullptr");
		return nullptr;
	}

	// Get information from the agent.
	PathingAgent* pPathingAgent = dynamic_cast<PathingAgent*>(pAgent);
	const Tilemap* pTilemap = pPathingAgent->GetTilemap();
	Kinematic& kinematic = pAgent->GetKinematic();

	if (!pPathingAgent && !pTilemap)
	{
		DWARN_TRACE("Agent is not a pathing agent or tilemap has not been set.");
		return nullptr;
	}

	// Arrive Behavior

	Vector2f delta = m_target - pAgent->GetPosition();
	float distance = delta.Length();

	// When we're close to the "next tile in the path" find the new one.
	if (distance < m_arriveRadius)
	{

		if(!Next())
		{
			kinematic.Stop();
			return m_pExitState;
		}
	}

	// calculate the desired speed
	float desiredSpeed = kinematic.GetMaxSpeed();
	if (distance < m_slowRadius)
	    desiredSpeed = kinematic.GetMaxSpeed() * distance / m_slowRadius;

	// turn our speed into a velocity, which is a combination of speed & direction 
	Vector2f targetVelocity = delta;
	targetVelocity.Normalize();
	targetVelocity *= desiredSpeed;

	// calculate the target acceleration based on the target velocity
	Vector2f targetAcceleration = targetVelocity - kinematic.GetVelocity();
	targetAcceleration /= 0.1f; // Time to target.

	// accelerate and face in the direction we're moving
	kinematic.Accelerate(targetAcceleration, dt);
	pAgent->GetLocation().SetOrientationFromDirection(kinematic.GetVelocity());

	return nullptr;
}

void FollowPathBehavior::OnTransitionEnter()
{
	m_pathIndex = 0;
	GoToWaypoint(m_pathIndex);
}

void FollowPathBehavior::OnTransitionExit()
{
	GetAgent()->GetKinematic().Stop();
}

bool FollowPathBehavior::Next()
{
	++m_pathIndex;
	return GoToWaypoint(m_pathIndex);
}

bool FollowPathBehavior::GoToWaypoint(size_t index)
{
	PathingAgent* pPathingAgent = dynamic_cast<PathingAgent*>(GetAgent());
	const Tilemap* pTilemap = pPathingAgent->GetTilemap();

	if (pPathingAgent)
	{
		Path* pPath = pPathingAgent->GetPath();

		if (index < pPath->Count())
		{
			Vector2 nextTilePos = pPath->GetWaypointAtIndex(index);
			m_target = pTilemap->TileToWorldPosition(nextTilePos);
			return true;
		}

		// Exit early, No warning
		return false;
	}

	DWARN_TRACE("Invalid PathingAgent");
	return false;
}
