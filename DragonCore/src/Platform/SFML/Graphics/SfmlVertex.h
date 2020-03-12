#pragma once

#include <SFML/Graphics/Vertex.hpp>
#include <Platform/SFML/SfmlHelpers.h>

namespace dragon
{
	class SfmlVertex
	{
	private:
		sf::Vertex m_data;

	public:

		SfmlVertex(Vector2f pos, Color color, Vector2f uv)
			: m_data(sf::Convert(pos), sf::Convert(color), sf::Convert(uv))
		{}

		// Accessors

		void SetPosition(Vector2f pos) { m_data.position = sf::Convert(pos); }
		Vector2f GetPosition(Vector2f pos) const { return sf::Convert(m_data.position); }

		void SetColor(Color color) { m_data.color = sf::Convert(color); }
		Color GetColor() const { return sf::Convert(m_data.color); }

		void SetTextureCoords(Vector2f pos) { m_data.texCoords = sf::Convert(pos); }
		Vector2f GetTextureCoords() const { return sf::Convert(m_data.texCoords); }

		// Utility for platform specific.
		auto& GetNativeVertex() { return m_data; }
		const auto& GetNativeVertex() const { return m_data; }
	};
}