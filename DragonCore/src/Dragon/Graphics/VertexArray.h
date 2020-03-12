#pragma once

#include <Dragon/Graphics/Vertex.h>
#include <Dragon/Graphics/Renderable.h>
#include <Dragon/Graphics/PrimitiveType.h>
#include <EASTL/vector.h>

namespace dragon
{
	class VertexArray : public Renderable
	{
		eastl::vector<Vertex> m_vertices;
		PrimitiveType m_type;

	public:

		VertexArray()
			: VertexArray(PrimitiveType::Lines)
		{}

		VertexArray(PrimitiveType type)
			: m_type(type)
		{}

		// Copy, Is valid but slow.
		VertexArray(const VertexArray&) = default;
		VertexArray& operator=(const VertexArray&) = default;

		// Move, Totally valid.
		VertexArray(VertexArray&&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		Vertex* Data() { return m_vertices.data(); }
		const Vertex* Data() const { return m_vertices.data(); }

		template<typename NativeType>
		NativeType* Convert() { return static_cast<NativeType*>(m_vertices.data()); }

		void Reserve(size_t size) { m_vertices.size(); }
		void Clear() { m_vertices.clear(); }

		Vertex& operator[](size_t index) { return m_vertices[index]; }
		const Vertex& operator[](size_t index) const { return m_vertices[index]; }

		// Inherited via Renderable
		virtual void Render(RenderTarget& target, RenderStates states) override;
	};
}