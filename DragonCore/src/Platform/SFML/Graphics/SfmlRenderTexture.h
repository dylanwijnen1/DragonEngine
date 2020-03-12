#pragma once

#include <Platform/SFML/SfmlHelpers.h>

namespace sf
{
	class RenderTexture;
	class RenderTarget;
	class Texture;
}

namespace dragon
{

	class SfmlRenderTexture
	{
		sf::RenderTexture* m_pTarget;

	public:

		SfmlRenderTexture() 
			: m_pTarget(nullptr) 
		{}

		~SfmlRenderTexture();

		// Move ok, Copying is bad...
		SfmlRenderTexture(const SfmlRenderTexture&) = delete;
		SfmlRenderTexture(SfmlRenderTexture&&) = default;

		SfmlRenderTexture& operator=(const SfmlRenderTexture&) = delete;
		SfmlRenderTexture& operator=(SfmlRenderTexture&&) = default;

		// Inherited from RenderTexture
		bool Init(Vector2f size);

		void Display();
		void Clear(Color color);

		sf::RenderTarget* GetNativeTarget();
		const sf::Texture* GetNativeTexture() const;
	};

}