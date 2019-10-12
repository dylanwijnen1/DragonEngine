#pragma once

#include <Dragon/Graphics/Camera.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics/RenderTexture.hpp>

namespace dragon
{

	class SfmlRenderTexture : public sf::RenderTexture
	{
	public:
		bool Init(Vector2f size) {  }

		void Display() { display(); }

		Vector2f GetSize() const;
		void SetSize(Vector2f size);

		void Clear(Color color) { clear(sf::Convert(color)); }

		void SetCamera(Camera camera);
		Camera GetCamera() const;

		sf::RenderTarget* GetNativeTarget() { return this; }

		sf::Texture* GetNativeTexture();
	};

}