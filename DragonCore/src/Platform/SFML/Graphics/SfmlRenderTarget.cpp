#include "SfmlRenderTarget.h"

#include <SFML/Graphics/VertexBuffer.hpp>

namespace dragon
{
	sf::Vector2u SfmlRenderTarget::getSize() const
	{
		Vector2f size = GetSize();
		return sf::Vector2u((sf::Uint32)size.x, (sf::Uint32)size.y);
	}

	void SfmlRenderTarget::Draw(const VertexArray& data, const RenderState& state = RenderState::Default)
	{
		//draw(data.GetBuffer(), data.Count(), data.GetType(), state);
	}

	void SfmlRenderTarget::Draw(const VertexBuffer& buffer, const RenderState& state = RenderState::Default)
	{
		// TODO: Use OpenGL Directly
	}

	void SfmlRenderTarget::Draw(Vertex* vertices, size_t len, VertexType type, const RenderState& state = RenderState::Default)
	{
		sf::PrimitiveType sfType = ConvertType(type);

		// Unfortunately requiring to 'new' due to conversion, could create an internal buffer to make this faster but why..
		// Cost of using SFML for drawing instead of OpenGL
		sf::Vertex* sfVertices = new sf::Vertex[len];
		ConvertVertices(vertices, sfVertices, len);

		sf::RenderStates sfStates = ConvertState(state);

		draw(sfVertices, len, sfType, sfStates);

		// Clean up
		delete sfVertices;
	}

	void SfmlRenderTarget::ConvertVertices(Vertex* pIn, sf::Vertex* pOut, size_t len) const
	{
		for (size_t i = 0; i < len; ++i)
		{
			pOut[i].color		= sf::Convert(pIn[i].color);
			pOut[i].texCoords	= sf::Convert(pIn[i].uv);
			pOut[i].position	= sf::Convert(pIn[i].position);
		}
	}

	sf::RenderStates SfmlRenderTarget::ConvertState(const RenderState& state) const
	{
		sf::RenderStates states;

		//states.texture = state.pTexture->GetNativeTexture();

		return states;
	}

	sf::PrimitiveType SfmlRenderTarget::ConvertType(VertexType type) const
	{
		switch (type)
		{
		case VertexType::Points:
			return sf::PrimitiveType::Points;
		case VertexType::Lines:
			return sf::PrimitiveType::Lines;
		case VertexType::LineStrip:
			return sf::PrimitiveType::LineStrip;
		case VertexType::Triangles:
			return sf::PrimitiveType::Triangles;
		case VertexType::TriangleStrip:
			return sf::PrimitiveType::TrianglesStrip;
		case VertexType::TriangleFan:
			return sf::PrimitiveType::TriangleFan;
		}
	}

}