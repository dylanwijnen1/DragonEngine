#pragma once

#include <Dragon/Graphics/Color.h>

// Helper methods
#include <Box2D/Common/b2Math.h>
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Collision/b2Collision.h>

namespace b2
{
	using namespace dragon;

	inline Vector2f Convert(b2Vec2 vec) { return Vector2f(vec.x, vec.y); }
	inline b2Vec2 Convert(Vector2f vec) { return b2Vec2(vec.x, vec.y); }

	inline b2Vec3 Convert(Vector3f vec) { return b2Vec3(vec.x, vec.y, vec.z); }
	inline Vector3f Convert(b2Vec3 vec) { return Vector3f(vec.x, vec.y, vec.z); }

	inline RectF Convert(b2AABB aabb) 
	{ 
		return RectF(
			aabb.upperBound.x - aabb.lowerBound.x,
			aabb.upperBound.y - aabb.lowerBound.y,
			aabb.lowerBound.x,
			aabb.lowerBound.y
		); 
	}

	inline b2AABB Convert(RectF rect)
	{
		b2AABB aabb;
		aabb.lowerBound.x = rect.x;
		aabb.lowerBound.y = rect.y;
		aabb.upperBound.x = rect.x + rect.width;
		aabb.upperBound.y = rect.y + rect.height;
		return aabb;
	}

	inline b2AABB Convert(Vector2f min, Vector2f max)
	{
		// TODO: Implement using new structure Bounds
		b2AABB aabb;
		return aabb;
	}

	inline Color Convert(b2Color color)
	{
		return Color(color.r, color.g, color.b, color.a);
	}

	inline b2Color Convert(Color color)
	{
		return b2Color(color.r, color.g, color.b, color.a);
	}
}