#include "@{PRJ_NAME}@Layer.h"

@{PRJ_NAME}@Layer::~@{PRJ_NAME}@Layer()
{

}

void @{PRJ_NAME}@Layer::OnAttach()
{

}

void @{PRJ_NAME}@Layer::OnDetach()
{
}

void @{PRJ_NAME}@Layer::Update(float dt)
{

}

void @{PRJ_NAME}@Layer::FixedUpdate(float dt)
{

}

void @{PRJ_NAME}@Layer::Render(dragon::RenderTarget& target)
{

}

void @{PRJ_NAME}@Layer::OnEvent(dragon::ApplicationEvent& ev)
{
	ev.Dispatch<dragon::KeyPressed>(this, &@{PRJ_NAME}@Layer::HandleKeyPressed);
	ev.Dispatch<dragon::KeyReleased>(this, &@{PRJ_NAME}@Layer::HandleKeyReleased);
	ev.Dispatch<dragon::MouseScrolled>(this, &@{PRJ_NAME}@Layer::HandleMouseScroll);
}

void @{PRJ_NAME}@Layer::HandleKeyPressed(dragon::KeyPressed& keyEvent)
{

}

void @{PRJ_NAME}@Layer::HandleKeyReleased(dragon::KeyReleased& keyEvent)
{

}

void @{PRJ_NAME}@Layer::HandleMouseScroll(dragon::MouseScrolled& mouseScrollEvent)
{

}