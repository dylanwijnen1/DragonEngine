#pragma once

#include <mathfu/rect.h>
#include <mathfu/matrix.h>

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
	inline void OutStream::Serialize(Vector2f vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y); 
	}

	template<>
	inline Vector2f InStream::Deserialize()
	{
		Vector2f vec;
		vec.x = Deserialize<float>();
		vec.y = Deserialize<float>();
		return vec;
	}

	template<>
	inline void OutStream::Serialize(Vector3f vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y);
		Serialize(vec.z);
	}

	template<>
	inline Vector3f InStream::Deserialize()
	{
		Vector3f vec;
		vec.x = Deserialize<float>();
		vec.y = Deserialize<float>();
		vec.z = Deserialize<float>();
		return vec;
	}

	template<>
	inline void OutStream::Serialize(Vector4f vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y);
		Serialize(vec.z);
		Serialize(vec.w);
	}

	template<>
	inline  Vector4f InStream::Deserialize()
	{
		Vector4f vec;
		vec.x = Deserialize<float>();
		vec.y = Deserialize<float>();
		vec.z = Deserialize<float>();
		vec.w = Deserialize<float>();
		return vec;
	}

	// Integral

	template<>
	inline void OutStream::Serialize(Vector2 vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y);
	}

	template<>
	inline Vector2 InStream::Deserialize()
	{
		Vector2 vec;
		vec.x = Deserialize<int>();
		vec.y = Deserialize<int>();
		return vec;
	}

	template<>
	inline void OutStream::Serialize(Vector3 vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y);
		Serialize(vec.z); 
	}

	template<>
	inline Vector3 InStream::Deserialize()
	{
		Vector3 vec;
		vec.x = Deserialize<int>();
		vec.y = Deserialize<int>();
		vec.z = Deserialize<int>();
		return vec;
	}

	template<>
	inline void OutStream::Serialize(Vector4 vec) 
	{ 
		Serialize(vec.x);
		Serialize(vec.y);
		Serialize(vec.z);
		Serialize(vec.w); 
	}

	template<>
	inline Vector4 InStream::Deserialize()
	{
		Vector4 vec;
		vec.x = Deserialize<int>();
		vec.y = Deserialize<int>();
		vec.z = Deserialize<int>();
		vec.w = Deserialize<int>();
		return vec;
	}

};
