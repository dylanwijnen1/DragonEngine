#include "PhysicsDebugRenderer.h"
#include <Dragon/Physics/Physics.h>

// For implementation see : https://github.com/slok/Box2D-and-SFML-demo/blob/master/src/DebugDraw.cpp

namespace dragon
{

	void PhysicsDebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{

	}

	void PhysicsDebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
	}

	void PhysicsDebugRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
	}

	void PhysicsDebugRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
	}

	void PhysicsDebugRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
	}

	void PhysicsDebugRenderer::DrawTransform(const b2Transform& xf)
	{
	}

	void PhysicsDebugRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
	{
	}

}
