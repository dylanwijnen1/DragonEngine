#pragma once

#include <Dragon/Graphics/Camera.h>

#include <Platform/SFML/SfmlHelpers.h>

#include <SFML/Graphics/RenderTarget.hpp>

namespace dragon
{
	class Window;

	class SfmlGraphics : public sf::RenderTarget
	{
		Vector2f m_size;
		Window* m_pWindow;

	public:

		SfmlGraphics() 
			: m_size(1024.f, 1024.f)
			, m_pWindow(nullptr)
		{}
		~SfmlGraphics() = default;

		SfmlGraphics(const SfmlGraphics&) = delete;
		SfmlGraphics(SfmlGraphics&&) = delete;
		SfmlGraphics& operator=(const SfmlGraphics&) = delete;
		SfmlGraphics& operator=(SfmlGraphics&&) = delete;

		Vector2f GetSize() const { return m_size; }
		void SetSize(Vector2f size) { m_size = size; }

		void SetCamera(Camera camera);
		virtual Camera GetCamera() const;

		void Clear(Color color) { clear(sf::Convert(color)); }
		void Display();

		void SetWindow(Window* pWindow) { m_pWindow = pWindow; }

		bool Init(Vector2f size);

		sf::RenderTarget* GetNativeTarget() { return this; }

	protected:
		sf::Vector2u getSize() const final override;
	};

}