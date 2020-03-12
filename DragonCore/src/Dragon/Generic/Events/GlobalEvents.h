#pragma once

#include <EASTL/unordered_map.h>
#include <EASTL/functional.h>
#include <EASTL/queue.h>

namespace dragon
{
	class GlobalEvents
	{

	public:

		template<typename Event>
		using Handle = size_t;

		template<typename Event>
		using EventListeners = eastl::unordered_map<Handle<Event>, eastl::function<bool(Event&)>>;

		template<typename Event>
		using EventQueue = eastl::queue<Event>;

		/// <summary>
		/// Immediately fire of the event, This allows the "invoker" to receive a return value.
		/// </summary>
		template<typename Event>
		static void Immediate(Event& ev)
		{
			Invoke(ev);
		}

		/// <summary>
		/// Queue up the event until it is ready to be processed.
		/// </summary>
		template<typename Event>
		static void Queue(Event&& ev)
		{
			auto& eventQueue = GetEventQueue<Event>();
			eventQueue.emplace_back(ev);
		}

		/// <summary>
		/// Processes the events that are queue'd
		/// </summary>
		template<typename Event>
		static void ProcessQueue()
		{
			auto& queue = GetEventQueue<Event>();
			while(!queue.empty())
			{
				Invoke(queue.front());
				queue.pop();
			}
		}

		template<typename Event, typename Func>
		static Handle<Event> AddListener(Func&& func)
		{
			// TODO: Determine wether to use func address or handle.
			static Handle<Event> s_lastHandle = 0;

			// Generate a unique handle.
			Handle<Event> handle = ++s_lastHandle;

			// Add the handler to the event listeners.
			GetEventListeners<Event>().emplace(handle, func);

			return handle;
		}

		template<typename Event>
		static void RemoveListener(Handle<Event> handle)
		{
			auto& listeners = GetEventListeners<Event>();
			if (auto result = listeners.find(handle); result != listeners.end())
			{
				listeners.erase(result);
			}
			else
			{
				DWARN("Attempting to erase listener with handle %i but it does not exist.", handle);
			}
		}

		template<typename Event>
		static void ClearListeners()
		{
			GetEventListeners<Event>().clear();
		}

	private:

		template<typename Event>
		static auto& GetEventListeners()
		{
			static EventListeners<Event> s_listeners;
			return s_listeners;
		}

		template<typename Event>
		static auto& GetEventQueue()
		{
			static EventQueue<Event> s_queue;
			return s_queue;
		}

		template<typename Event>
		static void Invoke(Event& ev)
		{
			auto& listeners = GetEventListeners<Event>();
			for (auto pair : listeners)
			{
				bool handled = pair.second(ev);
				if (handled)
					return;
			}
		}
	};

}