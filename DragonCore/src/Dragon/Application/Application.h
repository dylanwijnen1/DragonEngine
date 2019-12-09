#pragma once

#include <Dragon/Config.h>
#include <Dragon/Application/FpsCounter.h>

#include <chrono>

#include <EASTL/stack.h>

#include <Dragon/Application/Devices/Keyboard.h>
#include <Dragon/Application/Devices/Mouse.h>

/// \namespace dragon
namespace dragon
{
	class ApplicationEvent;
	class Layer;

	using namespace std::chrono_literals;

	/// <summary>
	/// The Core of the Engine
	/// </summary>
	class Application
	{
	private:

		/// <summary>
		/// True, If the application is still running.
		/// </summary>
		bool m_running;

		/// <summary>
		/// Targetted fixed update time.
		/// </summary>
		/// \default (1.0 / 60.0)
		double m_fixedStep;

		/// <summary>
		/// Layer stack holds pushed application layers.
		/// </summary>
		eastl::stack<Layer*> m_layers;
		
		/// \internal
		/// \{
		
		FpsCounter m_fixedCounter;
		FpsCounter m_updateCounter;
		FpsCounter m_drawCounter;

		using Clock = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Clock, Clock::duration>;

		using Duration = std::chrono::duration<double>;

		/// \}
		
		// Services
		class DragonSystem* m_pSystem;
		class AudioSystem* m_pAudioSystem;
		class Graphics* m_pGraphics;
		class Window* m_pWindow;

	public:

		Application()
			: m_running(false)
			, m_fixedStep(1.0 / 60.0)
			, m_pSystem(nullptr)
			, m_pAudioSystem(nullptr)
			, m_pGraphics(nullptr)
			, m_pWindow(nullptr)
		{}

		/// <summary>
		/// Destroy all the devices and layers
		/// </summary>
		virtual ~Application();

		/// <summary>
		/// Initializes the Application
		/// </summary>
		bool Init();

		/// <summary>
		/// Tell the application to shutdown
		/// </summary>
		void Shutdown();

		/// <summary>
		/// Start the application.
		/// </summary>
		void Run();

		/// <summary>
		/// Pushes a layer onto the stack.
		/// </summary>
		/// <code>
		/// PushLayer(new MyGameLayer());
		/// PushLayer(new UILayer());
		/// </code>
		/// <param name="pLayer">The layer to push.</param>
		void PushLayer(Layer* pLayer);

		/// <summary>
		/// Pops a layer from the stack.
		/// </summary>
		void PopLayer();

		size_t GetFixedRate() const { return m_fixedCounter.GetCount(); }
		size_t GetUpdateRate() const { return m_updateCounter.GetCount(); }
		size_t GetDrawRate() const { return m_drawCounter.GetCount();  }

	protected:
		virtual bool OnInit() { return true; }

	private:
		void FixedUpdate(float dt);
		void Render();
		void Update(float dt);

		void OnEvent(ApplicationEvent& ev);
	};

};