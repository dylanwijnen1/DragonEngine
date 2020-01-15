#pragma once

#include <Dragon/Application/@{PRJ_NAME}@Layer.h>
#include <Dragon/Application/Window/WindowEvents.h>

class @{PRJ_NAME}@Layer final : public dragon::Layer
{
public:
	@{PRJ_NAME}@Layer()
		: dragon::Layer("@{PRJ_NAME}@Layer")
	{}

	~@{PRJ_NAME}@Layer();

	@{PRJ_NAME}@Layer(const @{PRJ_NAME}@Layer&) = delete;
	@{PRJ_NAME}@Layer(@{PRJ_NAME}@Layer&&) = delete;
	@{PRJ_NAME}@Layer& operator=(const @{PRJ_NAME}@Layer&) = delete;
	@{PRJ_NAME}@Layer& operator=(@{PRJ_NAME}@Layer&&) = delete;

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