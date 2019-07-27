#pragma once

#include <Dragon/Application/ApplicationEvent.h>
#include <Dragon/Math/Math.h>
#include <Dragon/Application/Input/Key.h>
#include <Dragon/Application/Input/MouseButton.h>


namespace dragon
{
	//WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved
	class WindowClosed : public ApplicationEvent
	{
	public:
		EVENT_TYPE(WindowClosed)
	};

	class WindowResized : public ApplicationEvent
	{
	public:
		Vector2 m_newSize;
		
		EVENT_TYPE(WindowResized)
	};

	class WindowFocused : public ApplicationEvent
	{
	public:
		EVENT_TYPE(WindowFocused)
	};
	
	class WindowLostFocus : public ApplicationEvent
	{
	public:
		EVENT_TYPE(WindowLostFocus)
	};

	class WindowMoved : public ApplicationEvent
	{
	public:
		Vector2 m_newPosition;
		
		EVENT_TYPE(WindowMoved)
	};
	
	//KeyPressed, KeyReleased, TextInput,

	class KeyPressed : public ApplicationEvent
	{
	public:
		Key m_keyCode;
		unsigned int m_keyChar;
		bool m_shift;
		bool m_ctrl;
		bool m_alt;

		EVENT_TYPE(KeyPressed)
	};

	class KeyReleased : public ApplicationEvent
	{
	public:
		Key m_keyCode;
		unsigned int m_keyChar;
		bool m_shift;
		bool m_ctrl;
		bool m_alt;
		
		EVENT_TYPE(KeyReleased)
	};

	class TextInput : public ApplicationEvent
	{
	public:
		unsigned int m_unicodeChar;
		
		EVENT_TYPE(TextInput)
	};

	//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	
	class MouseButtonPressed : public ApplicationEvent
	{
	public:
		MouseButton m_button;
		Vector2f m_position;
		
		EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleased : public ApplicationEvent
	{
	public:
		MouseButton m_button;
		Vector2f m_position;
		
		EVENT_TYPE(MouseButtonReleased)
	};

	class MouseMoved : public ApplicationEvent
	{
	public:
		Vector2f m_position;
		
		EVENT_TYPE(MouseMoved)
	};

	class MouseScrolled : public ApplicationEvent
	{
	public:
		Vector2f m_position;
		float m_wheelDelta; // [-1.f, 1.f]
		
		EVENT_TYPE(MouseScrolled)
	};
}