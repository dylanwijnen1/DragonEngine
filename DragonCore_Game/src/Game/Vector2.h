#pragma once

#include <cmath>

template<typename Type>
struct _Vector2
{
public:
	using Self = _Vector2<Type>;
	Type x;
	Type y;

	_Vector2()
		: x((Type)0)
		, y((Type)0)
	{}

	_Vector2(Type x, Type y)
		: x(x)
		, y(y)
	{}

	float Length() const;
	Type LengthSqrd() const;

	static Type Distance(Self from, Self to) { return (to - from).Length(); }
	Type Distance(Self to) const { return Distance(*this, to); }

	static Type DistanceSqrd(Self from, Self to) { return (to - from).LengthSqrd(); }
	Type DistanceSqrd(Self to) const { return DistanceSqrd(*this, to); }

	void Normalize();
	Self Normalized() const;

	void RotateAroundOrigin(float angle, Self origin);

	Self& operator+=(Self vec);
	Self& operator-=(Self vec);

	template<typename OtherType>
	Self& operator+=(_Vector2<OtherType> vec);

	template<typename OtherType>
	Self& operator-=(_Vector2<OtherType> vec);

	Self& operator*=(float scalar);
	Self& operator/=(float scalar);

	Self operator*(float scalar);
	Self operator/(float scalar);
	Self operator+(Self rhs);
	Self operator-(Self rhs);
};

using Vector2 = _Vector2<int>;
using Vector2f = _Vector2<float>;

template<typename Type>
inline float _Vector2<Type>::Length() const
{
	return std::sqrtf((float)LengthSqrd());
}

template<typename Type>
inline Type _Vector2<Type>::LengthSqrd() const
{
	return x * x + y * y;
}

template<typename Type>
inline void _Vector2<Type>::Normalize()
{
	float mag = Length();
	if (mag > 0.0f)
	{
		x /= mag;
		y /= mag;
	}
}

template<typename Type>
inline _Vector2<Type> _Vector2<Type>::Normalized() const
{
	Self norm = *this; // Create a Copy
	norm.Normalize();
	return norm;
}

template<typename Type>
inline void _Vector2<Type>::RotateAroundOrigin(float angle, Self origin)
{
	const float kCosAngle = dragon::math::Cos(angle);
	const float kSinAngle = dragon::math::Sin(angle);

	Self result = *this;
	result -= origin;

	result.x = x * kCosAngle - y * kSinAngle;
	result.y = x * kSinAngle + y * kCosAngle;

	result += origin;

	x = result.x;
	y = result.y;
}

template<typename Type>
inline _Vector2<Type>& _Vector2<Type>::operator+=(Self vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<typename Type>
inline _Vector2<Type>& _Vector2<Type>::operator-=(Self vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<typename Type>
inline _Vector2<Type>& _Vector2<Type>::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

template<typename Type>
inline _Vector2<Type>& _Vector2<Type>::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

template<typename Type>
inline _Vector2<Type> _Vector2<Type>::operator*(float scalar)
{
	return Self{ (Type)(x * scalar), (Type)(y * scalar) };
}

template<typename Type>
inline _Vector2<Type> _Vector2<Type>::operator/(float scalar)
{
	return Self{ x / scalar, y / scalar };
}

template<typename Type>
inline _Vector2<Type> _Vector2<Type>::operator+(Self rhs)
{
	return Self{ x + rhs.x, y + rhs.y };
}

template<typename Type>
inline _Vector2<Type> _Vector2<Type>::operator-(Self rhs)
{
	return Self{ x - rhs.x, y - rhs.y };
}

template<typename Type>
template<typename OtherType>
inline _Vector2<Type>& _Vector2<Type>::operator+=(_Vector2<OtherType> vec)
{
	x += (Type)vec.x;
	y += (Type)vec.y;
	return *this;
}

template<typename Type>
template<typename OtherType>
inline _Vector2<Type>& _Vector2<Type>::operator-=(_Vector2<OtherType> vec)
{
	x -= (Type)vec.x;
	y -= (Type)vec.y;
	return *this;
}
