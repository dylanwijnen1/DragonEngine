#pragma once

#include <Dragon/Config.h>
#include <Dragon/Application/TimeStep.h>
#include <Dragon/Application/FpsCounter.h>

#include <EASTL/stack.h>

/// \namespace dragon
namespace dragon
{
	class ApplicationEvent;
	class Layer;

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
		/// Targetted render time
		/// </summary>
		double m_renderStep;

		/// <summary>
		/// Wether or not VSync is Enabled.
		/// </summary>
		bool m_isVSyncEnabled;

		/// <summary>
		/// Layer stack holds pushed application layers.
		/// </summary>
		eastl::stack<Layer*> m_layers;
		
		/// \internal
		/// \{
		
		FpsCounter m_fixedCounter;
		FpsCounter m_updateCounter;
		FpsCounter m_renderCounter;

		/// \}
		
		// Services
		System* m_pSystem;
		class AudioSystem* m_pAudioSystem;
		Window* m_pWindow;

	public:

		Application()
			: m_running(false)
			, m_isVSyncEnabled(false)
			// Timing
			, m_fixedStep(1.0 / 60.0)
			, m_renderStep(1.0 / 60.0)
			// Services
			, m_pSystem(nullptr)
			, m_pAudioSystem(nullptr)
			, m_pWindow(nullptr)
			// Counters
			, m_fixedCounter()
			, m_updateCounter()
			, m_renderCounter()
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
		size_t GetDrawRate() const { return m_renderCounter.GetCount();  }

		void SetVerticalSync(bool sync) { m_isVSyncEnabled = sync; }
		bool GetVerticalSync() const { return m_isVSyncEnabled; }

	protected:
		virtual bool OnInit() { return true; }

	private:
		void FixedUpdate(TimeStep dt);
		void Render();
		void Update(TimeStep dt);

		bool OnEvent(ApplicationEvent& ev);
	};

};