#pragma once

#include <EASTL/string.h>

namespace dragon
{
	class ApplicationEvent;

	class Layer
	{
		eastl::string m_layerName;

	public:
		Layer() = delete;
		Layer(const char* name) : m_layerName(name) {}
		~Layer() = default;

		Layer(const Layer&) = default;
		Layer(Layer&&) = default;
		Layer& operator=(const Layer&) = default;
		Layer& operator=(Layer&&) = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update(float dt) = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Render() = 0;

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