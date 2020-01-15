#pragma once

#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Serialization/OutStream.h>

#include <glm/glm.hpp>

namespace dragon
{

	using Vector2f = glm::vec2;
	using Vector3f = glm::vec3;
	using Vector4f = glm::vec4;

	using Vector2 = glm::ivec2;
	using Vector3 = glm::ivec3;
	using Vector4 = glm::ivec4;

	using Vector2u = glm::uvec2;
	using Vector3u = glm::uvec3;
	using Vector4u = glm::uvec4;

	template<typename Type, size_t Amount>
	using _Vector = glm::vec<Amount, Type>;

	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;

	template<typename Type, size_t Rows, size_t Columns>
	using Matrix = glm::mat<Columns, Rows, Type>;

	using Quaternion = glm::quat;
	
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
