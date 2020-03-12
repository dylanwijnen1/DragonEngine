#include "Application.h"

#include <Dragon/Application/Layer.h>
#include <Dragon/Application/System/System.h>
#include <Dragon/Application/ApplicationEvent.h>

#include <Dragon/Generic/Events/GlobalEvents.h>

// Services
#include <Dragon/Application/Window/Window.h>
#include <Dragon/Application/Window/WindowEvents.h>

// Debugging
#include <Dragon/Debug.h>

#define APP_DIE(SERVICE, PSERVICE, ...) if(!PSERVICE->Init(__VA_ARGS__)) { DERR("["##SERVICE##"] could not be initialized, Exiting..."); return false; }
#define APP_CONTINUE(SERVICE, PSERVICE, ...) if(!PSERVICE->Init(__VA_ARGS__)) { DWARN("["##SERVICE##"] could not be intialized. Acting like nothing happened..."); }

#include <iostream>

namespace dragon
{

	Application::~Application()
	{
		m_pWindow->Close();

		delete m_pSystem;
		delete m_pWindow;

		// Delete Layers
		while (!m_layers.empty())
		{
			Layer* pLayer = m_layers.top();
			delete pLayer;

			m_layers.pop();
		}

#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		//delete m_pAudio;
#endif
	}

	bool Application::Init()
	{
		// System Service
		m_pSystem = new System();
		APP_DIE("System", m_pSystem);
		//m_pSystem->GetMemoryInfo();

		// Load Application Settings
		// APP_CONTINUE("DragonSettings", DragonSettings::GetInstance());

		// Window Service
		m_pWindow = new Window();
		APP_DIE("Window", m_pWindow, DRAGON_APP_NAME, DRAGON_WINDOW_WIDTH, DRAGON_WINDOW_HEIGHT);
		GlobalEvents::AddListener<ApplicationEvent>([this](ApplicationEvent& ev) -> bool { return OnEvent(ev); });

		// Audio Service, Die
		// m_pAudioSystem = DragonAudioSystem::Create();
		// APP_DIE("DragonAudioSystem", m_pAudioSystem);

		bool result = OnInit();
		
		DINFO("[DragonApplication] Application has finished initialization.");

		return result;
	}

	void Application::Shutdown()
	{
		DINFO("[DragonApplication] Application is shutting down.");
		m_running = false;
	}

	void Application::Run()
	{
		using seconds = std::chrono::duration<double>;

		m_running = true;
		DINFO("[DragonApplication] Application has started.");

		TimeStep::TimePoint start = TimeStep::now();
		TimeStep::TimePoint end = TimeStep::now();
		
		TimeStep fixedStep = TimeStep(seconds(m_fixedStep));

		TimeStep deltaTime = fixedStep; // Start frametime with targeted refresh rate.

		// Accumulates time, Once we accumulate more time than we call Application::FixedUpdate()
		double fixedAccumulator = 0.0;

		// Accumulates time for the rendering. Ignored when we have vSync enabled.
		double renderAccumulator = 0.0;

		while(m_running)
		{
			m_pWindow->ProcessEvents();

			// Fixed Update
			fixedAccumulator += deltaTime.Seconds();
			if (fixedAccumulator > m_fixedStep)
			{
				fixedAccumulator -= m_fixedStep;
				
				// Create a fixed time step.
				FixedUpdate(fixedStep);
			}

			// Rendering
			if (!m_isVSyncEnabled)
			{
				renderAccumulator += deltaTime.Seconds();
				if (renderAccumulator > m_renderStep)
				{
					renderAccumulator -= m_renderStep;
					Render();
				}
			}
			else
			{
				Render();
			}

			// Update
			Update(deltaTime);

			// Calculate deltaTime
			end = TimeStep::now();
			deltaTime = TimeStep(end - start);

			double deltaSeconds = deltaTime.Seconds();
			
			// Breakpoint was set or we're running slow.
			if (deltaSeconds > 1.0)
			{
				DWARN("[DragonApplication] Application is running slow. Frame took: %lf seconds.", deltaSeconds);
				
				// Reset Time Step to ensure we don't take a very large time step.
				deltaTime = fixedStep;
			}

			start = end;
		}
	}

	void Application::FixedUpdate(TimeStep dt)
	{
		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->FixedUpdate(dt);

		m_fixedCounter.Tick();
	}

	void Application::Render()
	{
		m_pWindow->Clear(Colors::Black);

		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->Render(*m_pWindow);

		m_pWindow->SwapBuffers();

		m_renderCounter.Tick();
	}

	void Application::Update(TimeStep dt)
	{
		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->Update(dt);

		m_updateCounter.Tick();
	}

	bool Application::OnEvent(ApplicationEvent& ev)
	{
		auto& layerStack = m_layers.get_container();

		// Propogate Events in Reverse
		for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
		{
			if (ev.IsHandled())
				return true;

			Layer* pLayer = *it;
			pLayer->OnEvent(ev);
		}

		// Listen for QuitEvent at last.
		if (ev.GetEventType() == ApplicationEventType::WindowClosed)
			this->Shutdown();

		return false;
	}

	void Application::PushLayer(Layer* pLayer)
	{
		m_layers.emplace_back(pLayer);
		pLayer->OnAttach();
	}

	void Application::PopLayer()
	{
		Layer* pLayer = m_layers.top();
		pLayer->OnDetach();

		m_layers.pop();

		delete pLayer;
	}

	//void Application::ShowDebugInfo()
	//{
	//	if (!m_drawDebugInfo)
	//		return;

	//	const float DISTANCE = 10.0f;
	//	static int corner = 0;
	//	ImGuiIO& io = ImGui::GetIO();
	//	
	//	if (corner != -1)
	//	{
	//		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
	//		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	//		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	//	}

	//	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	//	if (ImGui::Begin("Application Info", &m_drawDebugInfo, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	//	{
	//		ImGui::Text("(right-click to change position)");
	//		ImGui::Separator();

	//		ImGui::TextColored(Colors::Green, "Draws: %u", m_avgSteps.m_draws);
	//		ImGui::SameLine();
	//		ImGui::TextColored(Colors::LightGreen, "Update: %u", m_avgSteps.m_updates);
	//		//ImGui::SameLine();
	//		//ImGui::TextColored(Colors::Blue, "FixedUpdate: %u", m_avgSteps.m_fixedUpdates);
	//		
	//		if (ImGui::IsMousePosValid())
	//			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
	//		else
	//			ImGui::Text("Mouse Position: <invalid>");

	//		if (ImGui::BeginPopupContextWindow())
	//		{
	//			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
	//			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
	//			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
	//			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
	//			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
	//			if (m_drawDebugInfo && ImGui::MenuItem("Close")) m_drawDebugInfo = false;
	//			ImGui::EndPopup();
	//		}
	//	}
	//	ImGui::End();

	//}

};