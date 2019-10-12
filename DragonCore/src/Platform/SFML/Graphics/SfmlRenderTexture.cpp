#include "SfmlRenderTexture.h"

#include <Dragon/Application/Debugging/Debug.h>

namespace dragon
{

	Vector2f SfmlRenderTexture::GetSize() const
	{
		sf::Vector2u size = getSize();
		return { (float)size.x, (float)size.y };
	}

	void SfmlRenderTexture::SetSize(Vector2f size)
	{
		DWARN("Cannot set size of SfmlRenderTexture after it's been created.");
	}

	void SfmlRenderTexture::SetCamera(Camera camera)
	{
		sf::View view = getDefaultView();

		view.setCenter(sf::Convert(camera.m_position));
		view.setSize(sf::Convert(camera.m_size));
		view.setViewport(sf::Convert(camera.m_viewport));

		setView(view);
	}

	Camera SfmlRenderTexture::GetCamera() const
	{
		const sf::View& view = getView();

		Camera camera;
		camera.m_position = sf::Convert(view.getCenter());
		camera.m_size = sf::Convert(view.getSize());
		camera.m_viewport = sf::Convert(view.getViewport());

		return camera;
	}

	sf::Texture* SfmlRenderTexture::GetNativeTexture()
	{
		// TODO: Very unsafe const cast. But only way to reference the texture.
		return const_cast<sf::Texture*>(&getTexture());
	}

}