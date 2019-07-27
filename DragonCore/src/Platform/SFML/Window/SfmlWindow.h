#pragma once

#include <Dragon/Application/Window/DragonWindow.h>

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>


namespace dragon
{
	class SfmlWindow : public DragonWindow
	{
	private:
		sf::Window m_window;

	public:
		SfmlWindow() = default;
		~SfmlWindow();

		SfmlWindow(const SfmlWindow&) = default;
		SfmlWindow(SfmlWindow&&) = default;
		SfmlWindow& operator=(const SfmlWindow&) = default;
		SfmlWindow& operator=(SfmlWindow&&) = default;

		// Inherited via IWindow
		virtual bool Init(const char * pTitle, size_t width, size_t height) override;
		virtual void Close();
		virtual void ProcessEvents() override;
		virtual void* GetNativeWindowHandle() const override;
		virtual void SwapBuffers() override;

		virtual void SetPosition(int x, int y) override;
		Vector2 GetPosition() override;

		virtual void SetSize(size_t width, size_t height) override;
		Vector2 GetSize() override;

		//virtual void SetMousePosition(Vector2f mousePos) override;
		//virtual void DrawMouseCursor(bool draw) override;

	private:
		Key ConvertKey(sf::Keyboard::Key key) const;
		MouseButton ConvertButton(sf::Mouse::Button button) const;
	};
}