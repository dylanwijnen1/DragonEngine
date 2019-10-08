#pragma once

#include <Dragon/Graphics/Color.h>

//#include <Dragon/Physics/Components/...>
#include <Dragon/Physics/Components/RigidBody.h>
#include <Dragon/Physics/Components/Collider.h>
#include <Dragon/Physics/Components/BoxCollider.h>
#include <Dragon/Physics/Components/CircleCollider.h>
#include <Dragon/Physics/Components/PolygonCollider.h>

#include <Dragon/Generic/Math.h>

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
		aabb.lowerBound.x = rect.pos.x;
		aabb.lowerBound.y = rect.pos.y;
		aabb.upperBound.x = rect.pos.x + rect.size.x;
		aabb.upperBound.y = rect.pos.y + rect.size.y;
		return aabb;
	}

	inline b2AABB Convert(Vector2f min, Vector2f max)
	{
		b2AABB aabb;
		aabb.lowerBound = b2::Convert(Vector2f::Min(min, max));
		aabb.upperBound = b2::Convert(Vector2f::Max(min, max));
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