#include <Dragon/Application/Application.h>
#include <Dragon/Application/Layer.h>

class _PRJ_NAME_Layer : public dragon::Layer
{

public:
	_PRJ_NAME_Layer() : dragon::Layer("_PRJ_NAME_Layer") {}
	~_PRJ_NAME_Layer() = default;

	_PRJ_NAME_Layer(const _PRJ_NAME_Layer&) = delete;
	_PRJ_NAME_Layer(_PRJ_NAME_Layer&&) = delete;
	_PRJ_NAME_Layer& operator=(const _PRJ_NAME_Layer&) = delete;
	_PRJ_NAME_Layer& operator=(_PRJ_NAME_Layer&&) = delete;

	virtual void OnAttach() final override { }
	virtual void OnDetach() final override { }

	virtual void Update(float dt) final override {}
	virtual void FixedUpdate(float dt) final override {}
	virtual void Render(dragon::RenderTarget& target) final override {}
};

class _PRJ_NAME_App : public dragon::Application
{
	virtual bool OnInit() override
	{
		PushLayer(new _PRJ_NAME_Layer());
		return true;
	}
};

int main()
{
	_PRJ_NAME_App app;
	if (!app.Init())
		return 0;

	app.Run();

	return 0;
}