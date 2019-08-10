#pragma once

#include <Box2D/Common/b2Draw.h>
#include <Dragon/Graphics/Drawable.h>

namespace dragon
{
	class PhysicsDebugRenderer : public b2Draw
	{
		RenderTarget* m_pRenderTarget;

	public:

		PhysicsDebugRenderer(RenderTarget* pRenderTarget)
			: m_pRenderTarget(pRenderTarget)
		{
			// Set flags
			SetFlags(e_aabbBit | e_centerOfMassBit | e_jointBit | e_pairBit | e_shapeBit);
		}

		// Inherited via b2Draw
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
		virtual void DrawTransform(const b2Transform& xf) override;
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;
	};
}