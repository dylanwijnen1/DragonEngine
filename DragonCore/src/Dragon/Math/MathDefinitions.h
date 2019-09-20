#pragma once

#include <mathfu/rect.h>
#include <mathfu/matrix.h>

#include <Generic/InStream.h>
#include <Generic/OutStream.h>

namespace dragon
{

	using RectF = mathfu::Rect<float>;
	using Rect = mathfu::Rect<int>;

	using Vector2f = mathfu::Vector<float, 2>;
	using Vector3f = mathfu::Vector<float, 3>;
	using Vector4f = mathfu::Vector<float, 4>;

	using Vector2 = mathfu::Vector<int, 2>;
	using Vector3 = mathfu::Vector<int, 3>;
	using Vector4 = mathfu::Vector<int, 4>;

	using Matrix3 = mathfu::Matrix<float, 3, 3>;
	using Matrix4 = mathfu::Matrix<float, 4, 4>;

	using Transform = mathfu::AffineTransform;

	template<int Rows, int Columns>
	using Matrix = mathfu::Matrix<float, Rows, Columns>;

};

// Float
template<>
inline void OutStream::Write(const dragon::Vector2f& vec) { Write(vec.x); Write(vec.y); }

template<>
inline dragon::Vector2f InStream::Read()
{
	dragon::Vector2f vec;
	vec.x = Read<float>();
	vec.y = Read<float>();
	return vec;
}

template<>
inline void OutStream::Write(const dragon::Vector3f& vec) { Write(vec.x); Write(vec.y); Write(vec.z); }

template<>
inline dragon::Vector3f InStream::Read()
{
	dragon::Vector3f vec;
	vec.x = Read<float>();
	vec.y = Read<float>();
	vec.z = Read<float>();
	return vec;
}

template<>
inline void OutStream::Write(const dragon::Vector4f& vec) { Write(vec.x); Write(vec.y); Write(vec.w); }

template<>
inline  dragon::Vector4f InStream::Read()
{
	dragon::Vector4f vec;
	vec.x = Read<float>();
	vec.y = Read<float>();
	vec.w = Read<float>();
	return vec;
}

// Integral

template<>
inline void OutStream::Write(const dragon::Vector2& vec) { Write(vec.x); Write(vec.y); }

template<>
inline dragon::Vector2 InStream::Read()
{
	dragon::Vector2 vec;
	vec.x = Read<int>();
	vec.y = Read<int>();
	return vec;
}

template<>
inline void OutStream::Write(const dragon::Vector3& vec) { Write(vec.x); Write(vec.y); Write(vec.z); }

template<>
inline dragon::Vector3 InStream::Read()
{
	dragon::Vector3 vec;
	vec.x = Read<int>();
	vec.y = Read<int>();
	vec.z = Read<int>();
	return vec;
}

template<>
inline void OutStream::Write(const dragon::Vector4& vec) { Write(vec.x); Write(vec.y); Write(vec.w); }

template<>
inline dragon::Vector4 InStream::Read()
{
	dragon::Vector4 vec;
	vec.x = Read<int>();
	vec.y = Read<int>();
	vec.w = Read<int>();
	return vec;
}