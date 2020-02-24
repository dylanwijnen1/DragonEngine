#pragma once

#include <Dragon/Application/Layer.h>
#include <Dragon/Application/Window/WindowEvents.h>

#include <Game/Tilemap.h>

#include <Game/AI/Pathfinding/PathPlan.h>
#include <Game/AI/Pathfinding/PathingAgent.h>

class GameLayer : public dragon::Layer
{
	Tilemap m_tilemap;
	Vector2f m_mousePosition;
	Vector2 m_tileMousePosition;

	PathPlan m_pathPlan;
	PathingAgent m_agent;

	Vector2 m_start;
	Vector2 m_end;

public:
	virtual void OnAttach() override;

	// Inherited via Layer
	virtual void Update(float dt) override;
	virtual void FixedUpdate(float dt) override;
	virtual void Render(dragon::RenderTarget& target) override;

	virtual void OnEvent(dragon::ApplicationEvent& ev) override;

	void OnMouseReleasedEvent(dragon::MouseButtonReleased& ev);
	void OnMouseMovedEvent(dragon::MouseMoved& ev);
};