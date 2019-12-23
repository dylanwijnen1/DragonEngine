#include "Mouse.h"

#include <Dragon/Application/Application.h>

void dragon::Mouse::OnEvent(ApplicationEvent& ev)
{
	ev.Dispatch<MouseButtonPressed>(this, &Mouse::HandleMouseDown);
	ev.Dispatch<MouseButtonReleased>(this, &Mouse::HandleMouseUp);
	ev.Dispatch<MouseMoved>(this, &Mouse::HandleMouseMove);
	ev.Dispatch<MouseScrolled>(this, &Mouse::HandleMouseScroll);
}

bool dragon::Mouse::GetUp(MouseButton button) const
{
	return m_oldState[(size_t)button] && !m_currentState[(size_t)button];
}

bool dragon::Mouse::GetDown(MouseButton button) const
{
	return !m_oldState[(size_t)button] && m_currentState[(size_t)button];
}

float dragon::Mouse::GetTimeSinceLast(MouseButton button) const
{
	double time = Duration(PreciseClock::now() - m_lastPressedTime[(size_t)button]).count();
	return (float)time;
}

void dragon::Mouse::Update()
{
	m_oldState = m_currentState; // Copy
}

void dragon::Mouse::HandleMouseDown(MouseButtonPressed& ev)
{
	m_currentState[(size_t)ev.m_button] = true;
	m_lastPressedTime[(size_t)ev.m_button] = PreciseClock::now();
}

void dragon::Mouse::HandleMouseUp(MouseButtonReleased& ev)
{
	m_currentState[(size_t)ev.m_button] = false;
}

void dragon::Mouse::HandleMouseMove(MouseMoved& ev)
{
	m_mousePosition = ev.m_position;
}

void dragon::Mouse::HandleMouseScroll(MouseScrolled& ev)
{
	m_wheelDelta = ev.m_wheelDelta;
	m_wheelPosition = ev.m_position;
}