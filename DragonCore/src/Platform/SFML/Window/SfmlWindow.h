#pragma once

#include <Dragon/Config.h>

#include <Dragon/Graphics/Color.h>
#include <Dragon/Graphics/PrimitiveType.h>

#include <Dragon/Generic/Math.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace dragon
{
	class SfmlWindow
	{
	private:
		sf::RenderWindow m_window;

	public:

		SfmlWindow() = default;

		// Moving/Copying a window is silly.
		SfmlWindow(const SfmlWindow&) = delete;
		SfmlWindow(SfmlWindow&&) = delete;
		SfmlWindow& operator=(const SfmlWindow&) = delete;
		SfmlWindow& operator=(SfmlWindow&&) = delete;

		bool Init(const char * pTitle, size_t width, size_t height);

		void Close();
		void HasFocus() const;

		void SetWindowPosition(int x, int y);
		dragon::Vector2 GetWindowPosition() const;

		void SetWindowSize(size_t width, size_t height);
		dragon::Vector2 GetWindowSize() const;

		void ProcessEvents();

		void SwapBuffers();

		void Clear(dragon::Color color);

		void Draw(dragon::Vertex* pVertices, size_t vertexCount, dragon::PrimitiveType primitiveType);

		void* GetNativeWindowHandle() const;

		void* GetNativeTarget() { return this; }
	};
}