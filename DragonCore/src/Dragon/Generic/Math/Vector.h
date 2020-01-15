#pragma once

#include <Dragon/Generic/Serialization/OutStream.h>
#include <Dragon/Generic/Serialization/InStream.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// TODO: Serialization Functions

namespace dragon
{
	//
	// Vector2
	//

	using Vector2f = glm::vec2;
	using Vector2 = glm::ivec2;
	using Vector2u = glm::uvec2;

	template<typename Type, glm::qualifier Qualifier>
	struct StreamWriter<glm::tvec2<Type, Qualifier>>
	{
		void Write(OutStream& out, glm::tvec2<Type, Qualifier> vec)
		{
			out.Write(vec.x);
			out.Write(vec.y);
		}
	};

	template<typename Type, glm::qualifier Qualifier>
	struct StreamReader<glm::tvec2<Type, Qualifier>>
	{
		glm::tvec2<Type, Qualifier> Read(InStream& in)
		{
			glm::tvec2<Type, Qualifier> vec;
			vec.x = in.Read<float>();
			vec.y = in.Read<float>();
			return vec;
		}
	};

	//
	// Vector 3
	//

	using Vector3f = glm::vec3;
	using Vector3 = glm::ivec3;
	using Vector3u = glm::uvec3;

	template<typename Type, glm::qualifier Qualifier>
	struct StreamWriter<glm::tvec3<Type, Qualifier>>
	{
		void Write(OutStream& out, glm::tvec3<Type, Qualifier> vec)
		{
			out.Write(vec.x);
			out.Write(vec.y);
			out.Write(vec.z);
		}
	};

	template<typename Type, glm::qualifier Qualifier>
	struct StreamReader<glm::tvec3<Type, Qualifier>>
	{
		glm::tvec3<Type, Qualifier> Read(InStream& in)
		{
			glm::tvec3<Type, Qualifier> vec;
			vec.x = in.Read<Type>();
			vec.y = in.Read<Type>();
			vec.z = in.Read<Type>();
			return vec;
		}
	};

	//
	// Vector 4
	//

	using Vector4f = glm::vec4;
	using Vector4 = glm::ivec4;
	using Vector4u = glm::uvec4;

	template<typename Type, glm::qualifier Qualifier>
	struct StreamWriter<glm::tvec4<Type, Qualifier>>
	{
		void Write(OutStream& out, glm::tvec4<Type, Qualifier> vec)
		{
			out.Write(vec.x);
			out.Write(vec.y);
			out.Write(vec.z);
			out.Write(vec.w);
		}
	};

	template<typename Type, glm::qualifier Qualifier>
	struct StreamReader<glm::tvec4<Type, Qualifier>>
	{
		glm::tvec4<Type, Qualifier> Read(InStream& in)
		{
			glm::tvec4<Type, Qualifier> vec;
			vec.x = in.Read<Type>();
			vec.y = in.Read<Type>();
			vec.z = in.Read<Type>();
			vec.w = in.Read<Type>();
			return vec;
		}
	};

	//
	// Variable Length Vector
	//

	template<typename Type, size_t Amount>
	using Vector = glm::vec<Amount, Type>;

}