#pragma once

#include <glm/glm.hpp>

namespace dragon
{

	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;

	template<typename Type, size_t Rows, size_t Columns>
	using Matrix = glm::mat<Columns, Rows, Type>;

}