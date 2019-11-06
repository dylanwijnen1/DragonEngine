#include <Application/_PRJ_NAME_App.h>

int main()
{
	_PRJ_NAME_App app;
	if (!app.Init())
		return 0;

	app.Run();

	return 0;
}