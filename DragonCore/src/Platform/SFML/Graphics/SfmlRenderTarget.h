#pragma once

#include <Dragon/Graphics/RenderTarget.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace dragon
{
	// TODO: Instead of SFML drawing just use OpenGL drawing.
	class SfmlRenderTarget : public RenderTarget, sf::RenderTarget
	{
		// Inherited via RenderTarget
		virtual sf::Vector2u getSize() const override;

		// Inherited via RenderTarget
		virtual void Draw(const VertexArray& data, const RenderState& state = RenderState::Default) override;
		virtual void Draw(const VertexBuffer& buffer, const RenderState& state = RenderState::Default) override;
		virtual void Draw(Vertex* vertices, size_t len, VertexType type, const RenderState& state = RenderState::Default) override;

		void ConvertVertices(Vertex* pIn, sf::Vertex* pOut, size_t len) const;

		sf::PrimitiveType ConvertType(VertexType type) const;

		sf::RenderStates ConvertState(const RenderState& state) const;
	};

}