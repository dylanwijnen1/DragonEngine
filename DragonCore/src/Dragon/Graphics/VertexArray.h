#pragma once

namespace dragon
{
	class VertexArray
	{


	public:
		VertexArray() = default;
		~VertexArray() = default;

		VertexArray(const VertexArray&) = default;
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(const VertexArray&) = default;
		VertexArray& operator=(VertexArray&&) = default;


	};
}