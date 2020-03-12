#include "SfmlRenderTexture.h"

#include <SFML/Graphics/RenderTexture.hpp>

#include <Dragon/Debug.h>

namespace dragon
{

	SfmlRenderTexture::~SfmlRenderTexture()
	{
		delete m_pTarget;
	}

	bool SfmlRenderTexture::Init(Vector2f size)
	{
		if (m_pTarget)
		{
			DWARN("Attempted to reinitialize SfmlRenderTexture.");
			return false;
		}

		m_pTarget = new sf::RenderTexture();
		m_pTarget->create((unsigned int)size.x, (unsigned int)size.y);
		return true;
	}

	void SfmlRenderTexture::Display()
	{
		m_pTarget->display();
	}

	void SfmlRenderTexture::Clear(Color color)
	{
		m_pTarget->clear(sf::Convert(color));
	}

	sf::RenderTarget* SfmlRenderTexture::GetNativeTarget()
	{
		return m_pTarget;
	}

	const sf::Texture* SfmlRenderTexture::GetNativeTexture() const
	{
		return &m_pTarget->getTexture();
	}

}