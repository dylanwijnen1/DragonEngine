#pragma once

namespace dragon
{
	class Vertex;

	/// <summary>
	/// A vertex buffer is vertex data stored on the GPU
	/// </summary>
	class VertexBuffer
	{
		

	public:
		VertexBuffer() = default;
		VertexBuffer(Vertex* pVertices);
		~VertexBuffer() = default;

		VertexBuffer(const VertexBuffer&) = default;
		VertexBuffer(VertexBuffer&&) = default;
		VertexBuffer& operator=(const VertexBuffer&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;
	
	};
}