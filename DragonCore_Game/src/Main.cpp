#include <Application/ExampleApp.h>

/// The sole purpose of this Project is to show case certain features
/// And acts as a testing suite for graphics, physics, resource management, etc.
int main()
{
	ExampleApp app;
	if (app.Init())
	{
		//app.PushLayer(new ExampleLayer());

		app.Run();
	}

	return 0;
}