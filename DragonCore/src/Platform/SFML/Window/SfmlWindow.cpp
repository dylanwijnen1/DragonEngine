#include "SfmlWindow.h"

#include <Dragon/Generic/Math.h>
#include <Dragon/Application/Application.h>
#include <Dragon/Application/Window/WindowEvents.h>
#include <Dragon/Generic/Events/GlobalEvents.h>

#include <Platform/SFML/SfmlHelpers.h>


#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace dragon
{
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

	void SfmlWindow::HasFocus() const
	{
		m_window.hasFocus();
	}

	void SfmlWindow::ProcessEvents()
	{
		// TODO:
		auto dispatch = GlobalEvents::Immediate<dragon::ApplicationEvent>;
		//auto dispatch = [](dragon::ApplicationEvent& ev) {};

		sf::Event ev;
		while(m_window.pollEvent(ev))
		{
			switch (ev.type)
			{
				case sf::Event::EventType::Closed:                 ///< The window requested to be closed (no data)
				{
					dragon::WindowClosed e;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::Resized:                ///< The window was resized (data in event.size)
				{
					dragon::WindowResized e;
					e.m_newSize = dragon::Vector2(ev.size.width, ev.size.height);
					dispatch(e);
					break;
				}
				case sf::Event::EventType::LostFocus:              ///< The window lost the focus (no data)
				{
					//m_hasFocus = false;
					dragon::WindowLostFocus e;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::GainedFocus:            ///< The window gained the focus (no data)
				{
					//m_hasFocus = true;
					dragon::WindowFocused e;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::KeyPressed:             ///< A key was pressed (data in event.key)
				{
					dragon::KeyPressed e;
					e.m_alt = ev.key.alt;
					e.m_ctrl = ev.key.control;
					e.m_shift = ev.key.shift;
					e.m_keyCode = ConvertKey(ev.key.code);
					e.m_keyChar = (unsigned int)e.m_keyCode;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::KeyReleased:            ///< A key was released (data in event.key)
				{
					dragon::KeyReleased e;
					e.m_alt = ev.key.alt;
					e.m_ctrl = ev.key.control;
					e.m_shift = ev.key.shift;
					e.m_keyCode = ConvertKey(ev.key.code);
					e.m_keyChar = (unsigned int)e.m_keyCode;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::MouseWheelScrolled:     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
				{
					dragon::MouseScrolled e;
					e.m_position = dragon::Vector2f((float)ev.mouseWheelScroll.x, (float)ev.mouseWheelScroll.y);
					e.m_wheelDelta = ev.mouseWheelScroll.delta;
					dispatch(e);
					break;
				}
				case sf::Event::EventType::MouseButtonPressed:     ///< A mouse button was pressed (data in event.mouseButton)
				{
					dragon::MouseButtonPressed e;
					e.m_button = ConvertButton(ev.mouseButton.button);
					e.m_position = dragon::Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y);
					dispatch(e);
					break;
				}
				case sf::Event::EventType::MouseButtonReleased:    ///< A mouse button was released (data in event.mouseButton)
				{
					dragon::MouseButtonReleased e;
					e.m_button = ConvertButton(ev.mouseButton.button);
					e.m_position = dragon::Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y);
					dispatch(e);
					break;
				}
				case sf::Event::EventType::MouseMoved:             ///< The mouse cursor moved (data in event.mouseMove)
				{
					dragon::MouseMoved e;
					e.m_position = dragon::Vector2f((float)ev.mouseMove.x, (float)ev.mouseMove.y);
					dispatch(e);
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

	void SfmlWindow::Clear(dragon::Color color)
	{
		m_window.clear(sf::Convert(color));
	}

	void SfmlWindow::Draw(dragon::Vertex* pVertices, size_t vertexCount, dragon::PrimitiveType primitiveType)
	{
		// TODO: Do not use reinterpret cast but do a safe cast.
		sf::Vertex* pSfVertices = reinterpret_cast<sf::Vertex*>(pVertices);
		sf::PrimitiveType sfType = sf::ConvertPrimitiveType(primitiveType);

		m_window.draw(pSfVertices, vertexCount, sfType);
	}

	void SfmlWindow::SetWindowPosition(int x, int y)
	{
		m_window.setPosition(sf::Vector2i(x, y));
	}

	dragon::Vector2 SfmlWindow::GetWindowPosition() const
	{
		return sf::Convert(m_window.getPosition());
	}

	void SfmlWindow::SetWindowSize(size_t width, size_t height)
	{
		m_window.setSize(sf::Vector2u((unsigned int)width, (unsigned int)height));
	}

	dragon::Vector2 SfmlWindow::GetWindowSize() const
	{
		sf::Vector2u size = m_window.getSize();
		return dragon::Vector2((int)size.x, (int)size.y);
	}

}