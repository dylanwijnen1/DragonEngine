#include "SfmlTexture.h"

#include <SFML/Graphics/Texture.hpp>

bool sf::SfmlTexture::LoadFromFile(const char* filename)
{
	sf::Texture* m_pTexture = new sf::Texture();

	if (!m_pTexture->loadFromFile(filename))
	{
		Destroy();
		return false;
	}

	return true;
}

bool sf::SfmlTexture::LoadFromMemory(const dragon::Byte* pData, size_t size)
{
	sf::Texture* m_pTexture = new sf::Texture();

	if (!m_pTexture->loadFromMemory((void*)pData, size))
	{
		Destroy();
		return false;
	}

	return true;
}

void sf::SfmlTexture::Destroy()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

dragon::Vector2f sf::SfmlTexture::GetSize() const
{
	dragon::Vector2f size = { 0.f, 0.f };

	if (m_pTexture)
	{
		Vector2u texSize = m_pTexture->getSize();
		size.x = (float)texSize.x;
		size.y = (float)texSize.y;
	}

	return size;
}
