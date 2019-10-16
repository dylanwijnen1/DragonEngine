#pragma once

#include <EASTL/string.h>

namespace dragon
{

	enum class ApplicationEventType
	{
		None = 0,
		WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, TextInput,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

#define EVENT_TYPE(type) \
	static ApplicationEventType GetStaticType() { return ApplicationEventType::##type; }\
	virtual ApplicationEventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }

	/// <summary>
	/// Base class for WindowEvent
	/// </summary>
	class ApplicationEvent
	{
	private:
		bool m_handled;

	public:
		ApplicationEvent() : m_handled(false) {}
		virtual ~ApplicationEvent() = default;

		ApplicationEvent(const ApplicationEvent&) = default;
		ApplicationEvent(ApplicationEvent&&) = default;
		ApplicationEvent& operator=(const ApplicationEvent&) = default;
		ApplicationEvent& operator=(ApplicationEvent&&) = default;

		virtual ApplicationEventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual eastl::string ToString() const { return GetName(); };

		template<typename EventType, typename Func>
		void Dispatch(Func&& func)
		{
			if (GetEventType() == EventType::GetStaticType())
			{
				func(static_cast<EventType&>(*this));
			}
		}

		template<typename EventType, typename Obj, typename Func>
		void Dispatch(Obj* pObj, Func&& func)
		{
			if (GetEventType() == EventType::GetStaticType())
			{
				eastl::apply(eastl::forward<Func>(func), eastl::make_tuple(pObj, static_cast<EventType&>(*this)));
			}
		}

		void Done() { m_handled = true; }
		bool IsHandled() const { return m_handled; }
	};
}