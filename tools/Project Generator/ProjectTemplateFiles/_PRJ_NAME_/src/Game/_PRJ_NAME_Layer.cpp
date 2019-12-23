#include "_PRJ_NAME_Layer.h"

_PRJ_NAME_Layer::~_PRJ_NAME_Layer()
{

}

void _PRJ_NAME_Layer::OnAttach()
{

}

void _PRJ_NAME_Layer::OnDetach()
{
}

void _PRJ_NAME_Layer::Update(float dt)
{

}

void _PRJ_NAME_Layer::FixedUpdate(float dt)
{

}

void _PRJ_NAME_Layer::Render(dragon::RenderTarget& target)
{

}

void _PRJ_NAME_Layer::OnEvent(dragon::ApplicationEvent& ev)
{
	ev.Dispatch<dragon::KeyPressed>(this, &_PRJ_NAME_Layer::HandleKeyPressed);
	ev.Dispatch<dragon::KeyReleased>(this, &_PRJ_NAME_Layer::HandleKeyReleased);
	ev.Dispatch<dragon::MouseScrolled>(this, &_PRJ_NAME_Layer::HandleMouseScroll);
}

void _PRJ_NAME_Layer::HandleKeyPressed(dragon::KeyPressed& keyEvent)
{

}

void _PRJ_NAME_Layer::HandleKeyReleased(dragon::KeyReleased& keyEvent)
{

}

void _PRJ_NAME_Layer::HandleMouseScroll(dragon::MouseScrolled& mouseScrollEvent)
{

}