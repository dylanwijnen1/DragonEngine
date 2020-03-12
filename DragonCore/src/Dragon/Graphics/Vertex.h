#pragma once

#include <Dragon/Config.h>
#include <Dragon/Generic/Math.h>
#include <Dragon/Graphics/Color.h>

namespace dragon
{
	template<typename VertexImpl>
	class _Vertex
	{
	private:
		VertexImpl m_impl;

	public:

		_Vertex(Vector2f pos, Color color, Vector2f uv)
			: m_impl(pos, color, uv)
		{}

		_Vertex(Vector2f pos, Color color)
			: _Vertex(pos, color, { 0.0f, 0.0f })
		{}

		explicit _Vertex(const VertexImpl& vertex)
			: m_impl(vertex)
		{}

		// Accessors

		void SetPosition(Vector2f pos) { m_impl.SetPosition(pos); }
		Vector2f GetPosition(Vector2f pos) const { return m_impl.GetPosition(pos); }

		void SetColor(Color color) { m_impl.SetColor(color); }
		Color GetColor() const { return m_impl.GetColor(color); }

		void SetTextureCoords(Vector2f pos) { m_impl.SetTextureCoords(pos); }
		Vector2f GetTextureCoords() const { return m_impl.GetTextureCoords(); }

		// Utility for platform specific.
		auto& GetNativeVertex() { return m_impl.GetNativeVertex(); }
		const auto& GetNativeVertex() const { return m_impl.GetNativeVertex(); }
	};

}

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML

#include <Platform/SFML/Graphics/SfmlVertex.h>
namespace dragon
{
	using Vertex = _Vertex<SfmlVertex>;
}

#elif DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_NONE

namespace dragon
{
	using Vertex = nullptr;
}

#else
#error "Unsupported Renderskin Vertex"
#endif