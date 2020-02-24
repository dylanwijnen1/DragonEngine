#include "SfmlRenderTexture.h"

#include <SFML/Graphics/RenderTexture.hpp>

namespace dragon
{
	void SfmlRenderTexture::OnCameraChanged(Camera camera)
	{
		sf::View view = m_pTarget->getDefaultView();

		m_pTarget->setView(view);
	}

	void SfmlRenderTexture::OnSizeChanged(Vector2f size)
	{
		//TODO: Needs testing. This could not be possibly.
		m_pTarget->create((unsigned int)size.x, (unsigned int)size.y);
	}

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

	const void* SfmlRenderTexture::GetNativeTexture() const
	{
		return &(m_pTarget->getTexture());
	}

}