#include "Application.h"

#include <Dragon/Application/Layer.h>
#include <Dragon/Application/ApplicationEvent.h>

// Python Module
#include <Dragon/dragon_module.h>

// Services
#include <Dragon/Application/System/DragonSystem.h>
#include <Dragon/Application/Window/DragonWindow.h>

#if defined(DRAGON_DEBUG)
	#define APP_DIE(SERVICE, PSERVICE, ...) if(!PSERVICE->Init(__VA_ARGS__)) { ERR("["##SERVICE##"] could not be initialized, Exiting..."); return false; }
	#define APP_CONTINUE(SERVICE, PSERVICE, ...) if(!PSERVICE->Init(__VA_ARGS__)) { WARN("["##SERVICE##"] could not be intialized. Acting like nothing happened..."); }
#elif defined(DRAGON_RELEASE)
	#define APP_DIE(...) 
	#define APP_CONTINUE(...) 
#endif

#include <iostream>

namespace py = pybind11;

namespace dragon
{

	Application::~Application()
	{
		delete m_pSystem;
		delete m_pWindow;

#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
		//delete m_pGraphics;
		//delete m_pAudio;
#endif

		// Cleanup python bindings
		m_dragonModule.release();
		py::finalize_interpreter();
	}

	bool Application::Init()
	{
		if(!Debug::GetInstance().Init())
			WARN("[DragonDebug] could not be intialized. Acting like nothing happened...");

		// System Service
		m_pSystem = DragonSystem::Create();
		APP_DIE("DragonSystem", m_pSystem);
		Debug::GetInstance().SetSystem(m_pSystem);

		// Initialize python bindings
		py::initialize_interpreter();
		
		// TODO: Find a way to disable exceptions in the pybind11 module.
		try
		{
			m_dragonModule = py::module::import("pydragon");
		}
		catch (const std::exception& e)
		{
			ERR("[PyDragon] %s", e.what());
		}


		// Load Application Settings
		// APP_CONTINUE("DragonSettings", DragonSettings::GetInstance());

		// Window Service
		m_pWindow = m_pSystem->CreateSystemWindow();
		APP_DIE("DragonWindow", m_pWindow, APP_NAME, DRAGON_WINDOW_WIDTH, DRAGON_WINDOW_HEIGHT);
		m_pWindow->SetEventCallback([this] (ApplicationEvent & ev) { Application::OnEvent(ev); });

#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE

		// TODO: Take Audio service out of the renderskin, We will be using FMOD for the Audio System so it does not rely on SFML
		// Audio Service, Die
		// m_pAudioSystem = DragonAudioSystem::Create();
		// APP_DIE("DragonAudioSystem", m_pAudioSystem);

		// Graphics Service, Die
		// m_pGraphics = m_pWindow->CreateGraphicsContext();??
		// m_pGraphics = DragonGraphics::CreateContext();
		// APP_DIE("DragonGraphics", m_pGraphics);

#endif

		return OnInit();
	}

	void Application::Shutdown()
	{
		LOG("[DragonApplication] Application is shutting down.");
		m_pWindow->Close();
		m_running = false;
	}

	void Application::Run()
	{
		m_running = true;
		LOG("[DragonApplication] Application has started.");

		TimePoint start = Clock::now();
		TimePoint end = Clock::now();
		
		double deltaTime = m_fixedStep; // Start frametime with targeted refresh rate.

		// Accumulates time, Once we accumulate more time than we call Application::FixedUpdate()
		double fixedAccumulator = 0.0;

		while(m_running)
		{
			m_pWindow->ProcessEvents();

			// Fixed Update
			fixedAccumulator += deltaTime;
			if (fixedAccumulator > m_fixedStep)
			{
				fixedAccumulator -= m_fixedStep;
				FixedUpdate((float)m_fixedStep);
			}

			// Update
			Update((float)deltaTime);

#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE
			// Render
			Render();
#endif

			// Calculate deltaTime
			end = Clock::now();
			deltaTime = Duration(end - start).count();
			
			// Breakpoint was set or we're running slow.
			if (deltaTime > 1.0)
			{
				WARN("[DragonApplication] Application is running slow. Frame took: %d seconds.", deltaTime);
				deltaTime = m_fixedStep;
			}

			start = end;

		}
	}

	void Application::FixedUpdate(float dt)
	{
		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->FixedUpdate(dt);

		m_fixedCounter.Tick();
	}

#if DRAGON_RENDERSKIN != DRAGON_RENDERSKIN_NONE

	void Application::Render()
	{
		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->Render();

		m_drawCounter.Tick();
	}

#endif

	void Application::Update(float dt)
	{
		auto& layerStack = m_layers.get_container();
		for (Layer* pLayer : layerStack)
			pLayer->Update(dt);

		m_updateCounter.Tick();
	}

	void Application::OnEvent(ApplicationEvent& ev)
	{
		auto& layerStack = m_layers.get_container();

		// Propogate Events in Reverse
		for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
		{
			if (ev.IsHandled())
				break;

			Layer* pLayer = *it;
			pLayer->OnEvent(ev);
		}
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