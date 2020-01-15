#pragma once

#include <Dragon/Generic/Math/Vector.h>

// TODO: Serialization Functions

namespace dragon
{
	/// <summary>
	/// Bounds are very similar to Rectangle however they are different in the way they are stored.
	/// Bounds are stored with the intention of the upper bound meaning { top, left } corner and the lower bound meaning the { bottom, right } corner
	/// </summary>
	template<typename Type>
	struct _Bounds
	{
		using Vec2 = Vector<Type, 2>;

	public:

#pragma region Constructors

		_Bounds(Vec2 lower, Vec2 upper)
			: lower(lower)
			, upper(upper)
		{}

		_Bounds(Type left, Type top, Type right, Type bottom)
			: left(left)
			, top(top)
			, right(right)
			, bottom(bottom)
		{}

#pragma endregion


		inline static constexpr Type kZero = (Type)0; // Zero Type.

		union
		{
			struct { Type left, top, right, bottom; }; // x1, y1, x2, y2
			struct { Vec2 lower, upper; }; // { x, y }[0], { x, y }[1]
		};

		constexpr Vec2 GetCenter() const
		{
			return GetPointAtOrigin(0.5f, 0.5f);
		}

		template<typename ScalarType>
		constexpr Vec2 GetPointAtOrigin(ScalarType originX, ScalarType originY) const
		{
			const Type kWidth = right - left;
			const Type kHeight = bottom - top;

			// TODO: Replace __FUNSIG__ with DRAGON_FUNC_SIG which grabs the nicest compiler specific variant.
			static_assert(eastl::is_scalar_v<ScalarType>, __FUNCSIG__ " ScalarType not a scalar value.");
			return Vec2{ left + (Type)(kWidth * originX), top + (Type)(kHeight * originY) };
		}

		template<typename ScalarType>
		constexpr _Bounds GetBoundsAtOrigin(ScalarType originX, ScalarType originY) const
		{
			_Bounds bounds;

			const Type kWidth = right - left;
			const Type kHeight = bottom - top;

			bounds.lower = GetPointAtOrigin(originX, originY);
			bounds.upper.x = bounds.lower.x + kWidth;
			bounds.upper.y = bounds.lower.y + kHeight;
			return bounds;
		}

		constexpr _Bounds GetIntersection(_Bounds other) const { return GetIntersection(*this, other); }

		// Returns the intersecting bounds. If not intersecting returns an empty bounds.
		constexpr static _Bounds GetIntersection(_Bounds boundsA, _Bounds boundsB)
		{
			Type left = dragon::math::Max(boundsA.left, boundsB.left);
			Type top = dragon::math::Max(boundsA.top, boundsB.top);

			Type right = dragon::math::Min(boundsA.right, boundsB.right);
			Type bottom = dragon::math::Min(boundsA.bottom, boundsB.bottom);

			if (left > right || top > bottom)
			{
				return { kZero, kZero, kZero, kZero };
			}

			_Bounds intersection { left, bottom, bottom, left };
			return intersection;
		}

		constexpr bool Intersects(_Bounds other) const { return Intersects(*this, other); }

		constexpr static bool Intersects(_Bounds boundsA, _Bounds boundsB)
		{
			_Bounds intersection = GetIntersection(boundsA, boundsB);
			return !(intersection.IsEmpty());
		}

		constexpr bool IsEmpty() const
		{
			return !(left == kZero || top == kZero || right == kZero || bottom == kZero);
		}

	};

	using BoundsF = _Bounds<float>;
	using Bounds = _Bounds<int>;
	using BoundsU = _Bounds<unsigned int>;
}