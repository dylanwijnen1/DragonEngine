#pragma once

#include <Dragon/Application/Layer.h>
#include <Dragon/Application/Window/WindowEvents.h>

class _PRJ_NAME_Layer final : public dragon::Layer
{
public:
	_PRJ_NAME_Layer()
		: dragon::Layer("_PRJ_NAME_Layer")
	{}

	~_PRJ_NAME_Layer();

	_PRJ_NAME_Layer(const _PRJ_NAME_Layer&) = delete;
	_PRJ_NAME_Layer(_PRJ_NAME_Layer&&) = delete;
	_PRJ_NAME_Layer& operator=(const _PRJ_NAME_Layer&) = delete;
	_PRJ_NAME_Layer& operator=(_PRJ_NAME_Layer&&) = delete;

	virtual void OnAttach() final override;
	virtual void OnDetach() final override;

	virtual void Update(float dt) final override;
	virtual void FixedUpdate(float dt) final override;
	virtual void Render(dragon::RenderTarget& target) final override;

	virtual void OnEvent(dragon::ApplicationEvent& ev) final override;

private:
	void HandleKeyPressed(dragon::KeyPressed& keyEvent);
	void HandleKeyReleased(dragon::KeyReleased& keyEvent);
	void HandleMouseScroll(dragon::MouseScrolled& mouseScrollEvent);
};