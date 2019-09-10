#include "SpriteRenderer.h"

#include <Dragon/Game/Game.h>
#include <Dragon/Graphics/RenderTarget.h>
#include <SFML/Graphics/Sprite.hpp>

namespace dragon
{
	void SpriteRenderer::SetTexture(Texture* pTexture)
	{
		m_vertices[0].position = ;
		m_vertices[1].position = ;
		m_vertices[2].position = ;
		m_vertices[3].position = ;

		m_vertices[0].uv = ;
		m_vertices[1].uv = ;
		m_vertices[2].uv = ;
		m_vertices[3].uv = ;
	}

	void SpriteRenderer::SetColor(Color color)
	{
		m_vertices[0].color = color;
		m_vertices[1].color = color;
		m_vertices[2].color = color;
		m_vertices[3].color = color;
	}

	Color SpriteRenderer::GetColor() const
	{
		return m_vertices[0].color;
	}

	void SpriteRenderer::Render(const RenderTarget& target, const RenderState& state) const
	{
		//state.m_pTexture = m_pTexture;
		//state.m_transform *= m_transform;

		target.Draw(m_vertices, 4, VertexType::TriangleStrip, state);
	}
}
