#include "SfmlWindow.h"

#include <Dragon/Generic/Math.h>
#include <Dragon/Application/Window/WindowEvents.h>

#include <SFML/Window.hpp>

namespace dragon
{
	SfmlWindow::~SfmlWindow()
	{
		m_window.close();
	}

	bool SfmlWindow::Init(const char * pTitle, size_t width, size_t height)
	{
		m_window.create(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), pTitle);
		m_window.setKeyRepeatEnabled(false);
		if(m_window.isOpen())
			return true;

		return false;
	}

	void SfmlWindow::Close()
	{
		m_window.close();
	}

	void SfmlWindow::ProcessEvents()
	{
		sf::Event ev;
		while(m_window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::EventType::Closed:                 ///< The window requested to be closed (no data)
				{
					WindowClosed e;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::Resized:                ///< The window was resized (data in event.size)
				{
					WindowResized e;
					e.m_newSize = Vector2(ev.size.width, ev.size.height);
					m_callback(e);
					break;
				}
				case sf::Event::EventType::LostFocus:              ///< The window lost the focus (no data)
				{
					m_hasFocus = false;
					WindowLostFocus e;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::GainedFocus:            ///< The window gained the focus (no data)
				{
					m_hasFocus = true;
					WindowFocused e;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::KeyPressed:             ///< A key was pressed (data in event.key)
				{
					KeyPressed e;
					e.m_alt = ev.key.alt;
					e.m_ctrl = ev.key.control;
					e.m_shift = ev.key.shift;
					e.m_keyCode = ConvertKey(ev.key.code);
					e.m_keyChar = (unsigned int)e.m_keyCode;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::KeyReleased:            ///< A key was released (data in event.key)
				{
					KeyReleased e;
					e.m_alt = ev.key.alt;
					e.m_ctrl = ev.key.control;
					e.m_shift = ev.key.shift;
					e.m_keyCode = ConvertKey(ev.key.code);
					e.m_keyChar = (unsigned int)e.m_keyCode;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::MouseWheelScrolled:     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
				{
					MouseScrolled e;
					e.m_position = Vector2f((float)ev.mouseWheelScroll.x, (float)ev.mouseWheelScroll.y);
					e.m_wheelDelta = ev.mouseWheelScroll.delta;
					m_callback(e);
					break;
				}
				case sf::Event::EventType::MouseButtonPressed:     ///< A mouse button was pressed (data in event.mouseButton)
				{
					MouseButtonPressed e;
					e.m_button = ConvertButton(ev.mouseButton.button);
					e.m_position = Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y);
					m_callback(e);
					break;
				}
				case sf::Event::EventType::MouseButtonReleased:    ///< A mouse button was released (data in event.mouseButton)
				{
					MouseButtonReleased e;
					e.m_button = ConvertButton(ev.mouseButton.button);
					e.m_position = Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y);
					m_callback(e);
					break;
				}
				case sf::Event::EventType::MouseMoved:             ///< The mouse cursor moved (data in event.mouseMove)
				{
					MouseMoved e;
					e.m_position = Vector2f((float)ev.mouseMove.x, (float)ev.mouseMove.y);
					m_callback(e);
					break;
				}
			}
		}
	}

	void* SfmlWindow::GetNativeWindowHandle() const
	{
		return reinterpret_cast<void*>(m_window.getSystemHandle());
	}

	void SfmlWindow::SwapBuffers()
	{
		m_window.display();
	}

	void SfmlWindow::SetPosition(int x, int y)
	{
		m_window.setPosition(sf::Vector2i(x, y));
	}

	Vector2 SfmlWindow::GetPosition()
	{
		sf::Vector2i pos = m_window.getPosition();
		return Vector2(pos.x, pos.y);
	}

	void SfmlWindow::SetSize(size_t width, size_t height)
	{
		m_window.setSize(sf::Vector2u((unsigned int)width, (unsigned int)height));
	}

	Vector2 SfmlWindow::GetSize()
	{
		sf::Vector2u size = m_window.getSize();
		return Vector2((int)size.x, (int)size.y);
	}

	Key SfmlWindow::ConvertKey(sf::Keyboard::Key key) const
	{
		Key returnKey = Key::Unknown;
		switch (key)
		{
		case sf::Keyboard::Key::Unknown: returnKey = Key::Unknown; break; ///< Unhandled key
		case sf::Keyboard::Key::A: returnKey = Key::A; break;        ///< The A key
		case sf::Keyboard::Key::B: returnKey = Key::B; break;            ///< The B key
		case sf::Keyboard::Key::C: returnKey = Key::C; break;            ///< The C key
		case sf::Keyboard::Key::D: returnKey = Key::D; break;            ///< The D key
		case sf::Keyboard::Key::E: returnKey = Key::E; break;            ///< The E key
		case sf::Keyboard::Key::F: returnKey = Key::F; break;            ///< The F key
		case sf::Keyboard::Key::G: returnKey = Key::G; break;            ///< The G key
		case sf::Keyboard::Key::H: returnKey = Key::H; break;            ///< The H key
		case sf::Keyboard::Key::I: returnKey = Key::I; break;            ///< The I key
		case sf::Keyboard::Key::J: returnKey = Key::J; break;            ///< The J key
		case sf::Keyboard::Key::K: returnKey = Key::K; break;            ///< The K key
		case sf::Keyboard::Key::L: returnKey = Key::L; break;            ///< The L key
		case sf::Keyboard::Key::M: returnKey = Key::M; break;            ///< The M key
		case sf::Keyboard::Key::N: returnKey = Key::N; break;            ///< The N key
		case sf::Keyboard::Key::O: returnKey = Key::O; break;            ///< The O key
		case sf::Keyboard::Key::P: returnKey = Key::P; break;            ///< The P key
		case sf::Keyboard::Key::Q: returnKey = Key::Q; break;            ///< The Q key
		case sf::Keyboard::Key::R: returnKey = Key::R; break;            ///< The R key
		case sf::Keyboard::Key::S: returnKey = Key::S; break;            ///< The S key
		case sf::Keyboard::Key::T: returnKey = Key::T; break;            ///< The T key
		case sf::Keyboard::Key::U: returnKey = Key::U; break;            ///< The U key
		case sf::Keyboard::Key::V: returnKey = Key::V; break;            ///< The V key
		case sf::Keyboard::Key::W: returnKey = Key::W; break;            ///< The W key
		case sf::Keyboard::Key::X: returnKey = Key::X; break;            ///< The X key
		case sf::Keyboard::Key::Y: returnKey = Key::Y; break;            ///< The Y key
		case sf::Keyboard::Key::Z: returnKey = Key::Z; break;            ///< The Z key
		case sf::Keyboard::Key::Num0: returnKey = Key::Num0; break;         ///< The 0 key
		case sf::Keyboard::Key::Num1: returnKey = Key::Num1; break;         ///< The 1 key
		case sf::Keyboard::Key::Num2: returnKey = Key::Num2; break;         ///< The 2 key
		case sf::Keyboard::Key::Num3: returnKey = Key::Num3; break;         ///< The 3 key
		case sf::Keyboard::Key::Num4: returnKey = Key::Num4; break;         ///< The 4 key
		case sf::Keyboard::Key::Num5: returnKey = Key::Num5; break;         ///< The 5 key
		case sf::Keyboard::Key::Num6: returnKey = Key::Num6; break;         ///< The 6 key
		case sf::Keyboard::Key::Num7: returnKey = Key::Num7; break;         ///< The 7 key
		case sf::Keyboard::Key::Num8: returnKey = Key::Num8; break;         ///< The 8 key
		case sf::Keyboard::Key::Num9: returnKey = Key::Num9; break;         ///< The 9 key
		case sf::Keyboard::Key::Escape: returnKey = Key::Escape; break;       ///< The Escape key
		case sf::Keyboard::Key::LControl: returnKey = Key::LControl; break;     ///< The left Control key
		case sf::Keyboard::Key::LShift: returnKey = Key::LShift; break;       ///< The left Shift key
		case sf::Keyboard::Key::LAlt: returnKey = Key::LAlt; break;         ///< The left Alt key
		case sf::Keyboard::Key::LSystem: returnKey = Key::LSystem; break;      ///< The left OS specific key: window (Windows and Linux): break; apple (MacOS X): break; ...
		case sf::Keyboard::Key::RControl: returnKey = Key::RControl; break;     ///< The right Control key
		case sf::Keyboard::Key::RShift: returnKey = Key::RShift; break;       ///< The right Shift key
		case sf::Keyboard::Key::RAlt: returnKey = Key::RAlt; break;         ///< The right Alt key
		case sf::Keyboard::Key::RSystem: returnKey = Key::RSystem; break;      ///< The right OS specific key: window (Windows and Linux): break; apple (MacOS X): break; ...
		case sf::Keyboard::Key::Menu: returnKey = Key::Menu; break;         ///< The Menu key
		case sf::Keyboard::Key::LBracket: returnKey = Key::LBracket; break;     ///< The [ key
		case sf::Keyboard::Key::RBracket: returnKey = Key::RBracket; break;     ///< The ] key
		case sf::Keyboard::Key::Semicolon: returnKey = Key::Semicolon; break;    ///< The ; key
		case sf::Keyboard::Key::Comma: returnKey = Key::Comma; break;        ///< The : break; key
		case sf::Keyboard::Key::Period: returnKey = Key::Period; break;       ///< The . key
		case sf::Keyboard::Key::Quote: returnKey = Key::Quote; break;        ///< The ' key
		case sf::Keyboard::Key::Slash: returnKey = Key::Slash; break;        ///< The / key
		case sf::Keyboard::Key::Backslash: returnKey = Key::Backslash; break;    ///< The \ key
		case sf::Keyboard::Key::Tilde: returnKey = Key::Tilde; break;        ///< The ~ key
		case sf::Keyboard::Key::Equal: returnKey = Key::Equal; break;        ///< The = key
		case sf::Keyboard::Key::Hyphen: returnKey = Key::Hyphen; break;       ///< The - key (hyphen)
		case sf::Keyboard::Key::Space: returnKey = Key::Space; break;        ///< The Space key
		case sf::Keyboard::Key::Enter: returnKey = Key::Enter; break;        ///< The Enter/Return keys
		case sf::Keyboard::Key::Backspace: returnKey = Key::Backspace; break;    ///< The Backspace key
		case sf::Keyboard::Key::Tab: returnKey = Key::Tab; break;          ///< The Tabulation key
		case sf::Keyboard::Key::PageUp: returnKey = Key::PageUp; break;       ///< The Page up key
		case sf::Keyboard::Key::PageDown: returnKey = Key::PageDown; break;     ///< The Page down key
		case sf::Keyboard::Key::End: returnKey = Key::End; break;          ///< The End key
		case sf::Keyboard::Key::Home: returnKey = Key::Home; break;         ///< The Home key
		case sf::Keyboard::Key::Insert: returnKey = Key::Insert; break;       ///< The Insert key
		case sf::Keyboard::Key::Delete: returnKey = Key::Delete; break;       ///< The Delete key
		case sf::Keyboard::Key::Add: returnKey = Key::Add; break;          ///< The + key
		case sf::Keyboard::Key::Subtract: returnKey = Key::Subtract; break;     ///< The - key (minus: break; usually from numpad)
		case sf::Keyboard::Key::Multiply: returnKey = Key::Multiply; break;     ///< The * key
		case sf::Keyboard::Key::Divide: returnKey = Key::Divide; break;       ///< The / key
		case sf::Keyboard::Key::Left: returnKey = Key::Left; break;         ///< Left arrow
		case sf::Keyboard::Key::Right: returnKey = Key::Right; break;        ///< Right arrow
		case sf::Keyboard::Key::Up: returnKey = Key::Up; break;           ///< Up arrow
		case sf::Keyboard::Key::Down: returnKey = Key::Down; break;         ///< Down arrow
		case sf::Keyboard::Key::Numpad0: returnKey = Key::Numpad0; break;      ///< The numpad 0 key
		case sf::Keyboard::Key::Numpad1: returnKey = Key::Numpad0; break;      ///< The numpad 1 key
		case sf::Keyboard::Key::Numpad2: returnKey = Key::Numpad0; break;      ///< The numpad 2 key
		case sf::Keyboard::Key::Numpad3: returnKey = Key::Numpad0; break;      ///< The numpad 3 key
		case sf::Keyboard::Key::Numpad4: returnKey = Key::Numpad0; break;      ///< The numpad 4 key
		case sf::Keyboard::Key::Numpad5: returnKey = Key::Numpad0; break;      ///< The numpad 5 key
		case sf::Keyboard::Key::Numpad6: returnKey = Key::Numpad0; break;      ///< The numpad 6 key
		case sf::Keyboard::Key::Numpad7: returnKey = Key::Numpad0; break;      ///< The numpad 7 key
		case sf::Keyboard::Key::Numpad8: returnKey = Key::Numpad0; break;      ///< The numpad 8 key
		case sf::Keyboard::Key::Numpad9: returnKey = Key::Numpad0; break;      ///< The numpad 9 key
		case sf::Keyboard::Key::F1: returnKey = Key::F1; break;           ///< The F1 key
		case sf::Keyboard::Key::F2: returnKey = Key::F2; break;           ///< The F2 key
		case sf::Keyboard::Key::F3: returnKey = Key::F3; break;           ///< The F3 key
		case sf::Keyboard::Key::F4: returnKey = Key::F3; break;           ///< The F4 key
		case sf::Keyboard::Key::F5: returnKey = Key::F3; break;           ///< The F5 key
		case sf::Keyboard::Key::F6: returnKey = Key::F3; break;           ///< The F6 key
		case sf::Keyboard::Key::F7: returnKey = Key::F3; break;           ///< The F7 key
		case sf::Keyboard::Key::F8: returnKey = Key::F3; break;           ///< The F8 key
		case sf::Keyboard::Key::F9: returnKey = Key::F3; break;           ///< The F9 key
		case sf::Keyboard::Key::F10: returnKey = Key::F3; break;          ///< The F10 key
		case sf::Keyboard::Key::F11: returnKey = Key::F3; break;          ///< The F11 key
		case sf::Keyboard::Key::F12: returnKey = Key::F3; break;          ///< The F12 key
		case sf::Keyboard::Key::F13: returnKey = Key::F3; break;          ///< The F13 key
		case sf::Keyboard::Key::F14: returnKey = Key::F3; break;          ///< The F14 key
		case sf::Keyboard::Key::F15: returnKey = Key::F3; break;          ///< The F15 key
		case sf::Keyboard::Key::Pause: returnKey = Key::Pause; break;        ///< The Pause key
		}

		return returnKey;
	}

	MouseButton SfmlWindow::ConvertButton(sf::Mouse::Button button) const
	{
		MouseButton returnButton = MouseButton::Unknown;
		switch (button)
		{
		case sf::Mouse::Button::Left: returnButton = MouseButton::Left; break;
		case sf::Mouse::Button::Middle: returnButton = MouseButton::Middle; break;
		case sf::Mouse::Button::Right: returnButton = MouseButton::Right; break;
		}

		return returnButton;
	}

}