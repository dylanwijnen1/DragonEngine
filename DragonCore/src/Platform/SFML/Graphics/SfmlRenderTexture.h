#pragma once

#include <Dragon/Graphics/RenderTexture.h>

#include <Platform/SFML/SfmlHelpers.h>



namespace sf
{
	class RenderTexture;
}

namespace dragon
{

	class SfmlRenderTexture final : public RenderTexture
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

		// Inherited from RenderTexture and RenderTarget
		bool Init(Vector2f size) final override;

		void Display() final override;
		void Clear(Color color) final override;

		void* GetNativeTarget() final override { return m_pTarget; }
		const void* GetNativeTexture() const final override;

	protected:

		// Inherited from RenderTexture and RenderTarget
		void OnCameraChanged(Camera camera) final override;
		void OnSizeChanged(Vector2f size) final override;
	};

}