#include "Keyboard.h"

#include <Dragon/Application/ApplicationEvent.h>

void dragon::Keyboard::OnEvent(ApplicationEvent& ev)
{
	ev.Dispatch<KeyPressed>(this, &Keyboard::HandleKeyDown);
	ev.Dispatch<KeyReleased>(this, &Keyboard::HandleKeyUp);
}

float dragon::Keyboard::GetTimeSinceLast(Key key) const
{
	float delta = (float)std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - m_lastPressedTime[(size_t)key]).count();
	return delta;
}

void dragon::Keyboard::Update()
{
	m_oldState = m_currentState;
}

void dragon::Keyboard::HandleKeyDown(KeyPressed& ev)
{
	m_currentState[(size_t)ev.m_keyCode] = true;
	m_lastPressedTime[(size_t)ev.m_keyCode] = std::chrono::high_resolution_clock::now();
}

void dragon::Keyboard::HandleKeyUp(KeyReleased& ev)
{
	m_currentState[(size_t)ev.m_keyCode] = false;
}
