#pragma once

#include <Dragon/Graphics/RenderTarget.h>
#include <EASTL/string.h>

namespace dragon
{
	class ApplicationEvent;

	class Layer
	{
		eastl::string m_layerName; // Mainly for debugging purposes.

	public:
		Layer() = delete;
		Layer(const char* name) : m_layerName(name) {}
		virtual ~Layer() = default;

		// Layers should not be copied.
		Layer(const Layer&) = delete;
		Layer(Layer&&) = delete;
		Layer& operator=(const Layer&) = delete;
		Layer& operator=(Layer&&) = delete;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update(float dt) = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Render(RenderTarget& target) = 0;

		virtual void OnEvent(ApplicationEvent& ev) {};
	};

	//struct NetworkMessage;

	//class NetworkLayer : public Layer
	//{
	//	virtual void OnNetworkMessage(NetworkMessage& msg) {}
	//};

	//class ImGuiLayer : public Layer
	//{
	//	virtual void OnImGuiRender() = 0;
	//};
}