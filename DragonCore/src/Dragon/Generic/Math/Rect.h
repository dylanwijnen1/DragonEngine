#pragma once

#include <Dragon/Generic/Math/MathDefinitions.h>
#include <EASTL/utility.h>
#include <EASTL/internal/type_fundamental.h>


namespace dragon
{
	template<typename Type>
	struct _Rect
	{
		using Vec2 = _Vector<Type, 2>;

	public:

		/// <summary>
		/// Unions are great...
		/// </summary>
		union
		{
			struct { Type x, y, width, height; };
			struct { Vec2 pos, size; };
		};

#pragma region Constructors

		// Uninitialized Constructor.
		_Rect(std::nullptr_t)
		{}

		_Rect(Type x, Type y, Type w, Type h)
			: x(x)
			, y(y)
			, width(w)
			, height(h)
		{}

		_Rect(Vec2 pos, Vec2 size)
			: pos(pos)
			, size(size)
		{}

		_Rect()
			: ((Type)0.0f, (Type)0.0f, (Type)0.0f, (Type)0.0f)
		{}

		_Rect(const _Rect& other)
		{
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
		}

		_Rect(_Rect&& other)
		{
			x = eastl::move(other.x);
			y = eastl::move(other.y);
			width = eastl::move(other.width);
			height = eastl::move(other.height);
		}

		_Rect& operator=(const _Rect& other)
		{
			x = other.x;
			y = other.y;
			width = other.width;
			height = other.height;
			return *this;
		}

		_Rect& operator=(_Rect&& other)
		{
			x = eastl::move(other.x);
			y = eastl::move(other.y);
			width = eastl::move(other.width);
			height = eastl::move(other.height);
			return *this;
		}

#pragma endregion

		/// <summary>
		/// Return the position of the center of the Rectangle.
		/// </summary>
		/// <returns></returns>
		Vec2 GetCenter() const
		{
			return GetPointAtOrigin(0.5f, 0.5f);
		}

		template<typename ScalarType>
		Vec2 GetPointAtOrigin(ScalarType originX, ScalarType originY)
		{
			return { pos.x + (Type)(size.x * originX), pos.y + (Type)(size.y * originY) };
		}

		/// <summary>
		/// Gets the rectangle at the specified origin
		/// </summary>
		/// <param name="origin">Must be of scalar type.</param>
		/// <returns></returns>
		template<typename ScalarType>
		_Rect GetRectAtOrigin(_Vector<ScalarType, 2> origin)
		{
			return GetRectAtOrigin(origin);
		}

		/// <summary>
		/// Gets the rectangle at the specified origin
		/// </summary>
		/// <param name="origin">Must be of scalar type.</param>
		/// <returns></returns>
		template<typename ScalarType>
		_Rect GetRectAtOrigin(ScalarType originX, ScalarType originY)
		{		
			auto origin = GetPointAtOrigin(originX, originY);
			auto delta = origin - pos;

			return { pos + delta, size };
		}

		/// <summary>
		/// Check if the given rectangle is touching the other rectangle.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool Intersects(_Rect other) const { return Intersects(*this, other); }

		static bool Intersects(_Rect left, _Rect right)
		{
			return (right.x >= left.x) && (right.y >= left.y) && (right.x + right.width <= left.x + left.width) && (right.y + right.height <= left.y + left.height);
		}

		bool Contains(Vec2 point) const { return Contains(*this, point); }
		static bool Contains(_Rect rect, Vec2 point)
		{
			return (point.x >= rect.x) && (point.x <= rect.x + rect.width) && (point.y >= rect.y) && (point.y <= rect.y + rect.height);
		}
	};

	//
	// Aliases
	//

	using Rect	= _Rect<int>;
	using RectF = _Rect<float>;
	using RectU = _Rect<unsigned int>;
}