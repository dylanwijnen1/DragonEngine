#include "Keyboard.h"

#include <Dragon/Application/ApplicationEvent.h>

void dragon::Keyboard::OnEvent(ApplicationEvent& ev)
{
	ev.Dispatch<KeyPressed>(this, &Keyboard::HandleKeyDown);
	ev.Dispatch<KeyReleased>(this, &Keyboard::HandleKeyUp);
}

float dragon::Keyboard::GetTimeSinceLast(Key key) const
{
	double time = Duration(PreciseClock::now() - m_lastPressedTime[(size_t)key]).count();
	return (float)time;
}

void dragon::Keyboard::Update()
{
	m_oldState = m_currentState;
}

bool dragon::Keyboard::GetDown(dragon::Key key) const
{
	return !m_oldState[(size_t)key] && m_currentState[(size_t)key];
}

bool dragon::Keyboard::GetUp(dragon::Key key) const
{
	return m_oldState[(size_t)key] && !m_currentState[(size_t)key];
}

void dragon::Keyboard::HandleKeyDown(KeyPressed& ev)
{
	m_currentState[(size_t)ev.m_keyCode] = true;
	m_lastPressedTime[(size_t)ev.m_keyCode] = PreciseClock::now();
}

void dragon::Keyboard::HandleKeyUp(KeyReleased& ev)
{
	m_currentState[(size_t)ev.m_keyCode] = false;
}
