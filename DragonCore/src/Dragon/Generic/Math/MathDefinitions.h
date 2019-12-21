#pragma once

#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Serialization/OutStream.h>

namespace dragon
{

	using RectF = mathfu::Rect<float>;
	using Rect = mathfu::Rect<int>;
	using RectU = mathfu::Rect<unsigned int>;

	template<typename Type>
	using _Rect = mathfu::Rect<Type>;

	using Vector2f = mathfu::Vector<float, 2>;
	using Vector3f = mathfu::Vector<float, 3>;
	using Vector4f = mathfu::Vector<float, 4>;

	using Vector2 = mathfu::Vector<int, 2>;
	using Vector3 = mathfu::Vector<int, 3>;
	using Vector4 = mathfu::Vector<int, 4>;

	using Vector2u = mathfu::Vector<unsigned int, 2>;
	using Vector3u = mathfu::Vector<unsigned int, 3>;
	using Vector4u = mathfu::Vector<unsigned int, 4>;

	template<typename Type, int Amount = 2>
	using _Vector = mathfu::Vector<Type, Amount>;

	using Matrix3 = mathfu::Matrix<float, 3, 3>;
	using Matrix4 = mathfu::Matrix<float, 4, 4>;

	using Transform = mathfu::AffineTransform;

	template<int Rows, int Columns>
	using Matrix = mathfu::Matrix<float, Rows, Columns>;
	
	// Float
	template<>
	inline void OutStream::Write(const Vector2f& vec) { Write(vec.x); Write(vec.y); }

	template<>
	inline Vector2f InStream::Read()
	{
		Vector2f vec;
		vec.x = Read<float>();
		vec.y = Read<float>();
		return vec;
	}

	template<>
	inline void OutStream::Write(const Vector3f& vec) { Write(vec.x); Write(vec.y); Write(vec.z); }

	template<>
	inline Vector3f InStream::Read()
	{
		Vector3f vec;
		vec.x = Read<float>();
		vec.y = Read<float>();
		vec.z = Read<float>();
		return vec;
	}

	template<>
	inline void OutStream::Write(const Vector4f& vec) { Write(vec.x); Write(vec.y); Write(vec.w); }

	template<>
	inline  Vector4f InStream::Read()
	{
		Vector4f vec;
		vec.x = Read<float>();
		vec.y = Read<float>();
		vec.w = Read<float>();
		return vec;
	}

	// Integral

	template<>
	inline void OutStream::Write(const Vector2& vec) { Write(vec.x); Write(vec.y); }

	template<>
	inline Vector2 InStream::Read()
	{
		Vector2 vec;
		vec.x = Read<int>();
		vec.y = Read<int>();
		return vec;
	}

	template<>
	inline void OutStream::Write(const Vector3& vec) { Write(vec.x); Write(vec.y); Write(vec.z); }

	template<>
	inline Vector3 InStream::Read()
	{
		Vector3 vec;
		vec.x = Read<int>();
		vec.y = Read<int>();
		vec.z = Read<int>();
		return vec;
	}

	template<>
	inline void OutStream::Write(const Vector4& vec) { Write(vec.x); Write(vec.y); Write(vec.w); }

	template<>
	inline Vector4 InStream::Read()
	{
		Vector4 vec;
		vec.x = Read<int>();
		vec.y = Read<int>();
		vec.w = Read<int>();
		return vec;
	}

};
