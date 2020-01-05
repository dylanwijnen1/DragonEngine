#pragma once

#include <Dragon/Graphics/RenderTarget.h>

namespace dragon
{
	class ApplicationEvent;

	class Layer
	{
	public:

		Layer() = default;
		virtual ~Layer() = default;

		// Layers should not be copied or moved.
		Layer(const Layer&) = delete;
		Layer(Layer&&) = delete;
		Layer& operator=(const Layer&) = delete;
		Layer& operator=(Layer&&) = delete;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void Update(float dt) = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Render(RenderTarget& target) = 0;

		virtual void BeginFrame() {}
		virtual void EndFrame() {}

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