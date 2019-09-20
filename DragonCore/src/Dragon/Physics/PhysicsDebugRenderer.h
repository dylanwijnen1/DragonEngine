#pragma once

#include <Box2D/Common/b2Draw.h>
#include <cstdint>

namespace dragon
{
	class RenderTarget;

	class PhysicsDebugRenderer : public b2Draw
	{
	protected:
		RenderTarget* m_pRenderTarget;

	public:

		PhysicsDebugRenderer()
			: PhysicsDebugRenderer(nullptr)
		{}

		PhysicsDebugRenderer
		(
			RenderTarget* pRenderTarget, 
			uint32_t flags = e_aabbBit | e_centerOfMassBit | e_jointBit | e_pairBit | e_shapeBit
		)
			: m_pRenderTarget(pRenderTarget)
		{
			// Set flags
			SetFlags(flags);
		}

		void SetRenderTarget(RenderTarget* pRenderTarget) { m_pRenderTarget = pRenderTarget; }

		// Inherited via b2Draw
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) = 0;
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) = 0;
		virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) = 0;
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) = 0;
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) = 0;
		virtual void DrawTransform(const b2Transform& xf) = 0;
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) = 0;
	};
}