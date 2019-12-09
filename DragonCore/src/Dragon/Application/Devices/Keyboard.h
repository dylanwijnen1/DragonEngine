#pragma once

#include <Dragon/Application/Window/WindowEvents.h>
#include <Dragon/Application/Input/Key.h>
#include <Dragon/Generic/Math.h>

#include <EASTL/array.h>

#include <chrono>

namespace dragon
{
	class ApplicationEvent;

	class Keyboard
	{
		using KeyStates = eastl::array<bool, (size_t)Key::kCount>;
		KeyStates m_oldState;
		KeyStates m_currentState;

		using TimePoint = std::chrono::high_resolution_clock::time_point;

		using KeyTimeData = eastl::array<TimePoint, (size_t)Key::kCount>;
		KeyTimeData m_lastPressedTime;

		Keyboard()
			: m_currentState()
			, m_oldState()
			, m_lastPressedTime()
		{}

	public:

		static Keyboard& GetInstance()
		{
			static Keyboard s_instance;
			return s_instance;
		}

		void OnEvent(ApplicationEvent& ev);

		bool GetUp(Key key) const { return !m_oldState[(size_t)key] && m_currentState[(size_t)key]; }
		bool GetDown(Key key) const { return m_oldState[(size_t)key] && m_currentState[(size_t)key]; }
		bool Get(Key key) const { return m_currentState[(size_t)key]; }

		float GetTimeSinceLast(Key key) const;

		void Update();

	private:

		// Event Handlers
		void HandleKeyDown(KeyPressed& ev);
		void HandleKeyUp(KeyReleased& ev);
	};
}