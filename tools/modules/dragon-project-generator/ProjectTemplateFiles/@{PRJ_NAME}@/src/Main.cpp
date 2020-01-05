#include <Application/@{PRJ_NAME}@App.h>

int main()
{
	@{PRJ_NAME}@App app;
	if (!app.Init())
		return 0;

	app.Run();

	return 0;
}