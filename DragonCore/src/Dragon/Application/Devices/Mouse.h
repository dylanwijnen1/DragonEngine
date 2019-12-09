#pragma once

#include <Dragon/Application/Window/WindowEvents.h>
#include <Dragon/Application/Input/MouseButton.h>
#include <Dragon/Generic/Math.h>

#include <EASTL/array.h>

#include <chrono>

namespace dragon
{
	class ApplicationEvent;

	class Mouse
	{
		Vector2f m_mousePosition;
		Vector2f m_wheelPosition;
		float m_wheelDelta;

		using MouseStates = eastl::array<bool, (size_t)MouseButton::kCount>;
		MouseStates m_oldState;
		MouseStates m_currentState;

		using TimePoint = std::chrono::high_resolution_clock::time_point;

		using MouseTimeData = eastl::array<TimePoint, (size_t)MouseButton::kCount>;
		MouseTimeData m_lastPressedTime;

		Mouse()
			: m_oldState()
			, m_currentState()
			, m_lastPressedTime()
			, m_wheelDelta(0.0f)
			, m_wheelPosition(0.0f)
			, m_mousePosition(0.0f)
		{}

	public:

		static Mouse& GetInstance()
		{
			static Mouse s_instance;
			return s_instance;
		}

		void OnEvent(ApplicationEvent& ev);

		bool GetUp(MouseButton button) const { return !m_oldState[(size_t)button] && m_currentState[(size_t)button]; }
		bool GetDown(MouseButton button) const { return m_oldState[(size_t)button] && m_currentState[(size_t)button]; }
		bool Get(MouseButton button) const { return m_currentState[(size_t)button]; }

		float GetTimeSinceLast(MouseButton button) const;

		dragon::Vector2f GetMousePosition() const { return m_mousePosition; }
		dragon::Vector2f GetWheelPosition() const { return m_wheelPosition; }
		float GetWheelDelta() const { return m_wheelDelta; }

		void Update();

	private:

		// Event Handlers
		void HandleMouseDown(MouseButtonPressed& ev);
		void HandleMouseUp(MouseButtonReleased& ev);
		void HandleMouseMove(MouseMoved& ev);
		void HandleMouseScroll(MouseScrolled& ev);
	};
}