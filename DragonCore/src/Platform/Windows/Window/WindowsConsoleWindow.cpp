//#include "WindowsConsoleWindow.h"
//
//#include <Windows.h>
//
///// <summary>
///// Generic Key/Mouse
///// https://docs.microsoft.com/en-us/windows/console/reading-input-buffer-events
///// 
///// Text
///// https://docs.microsoft.com/en-us/windows/console/getconsolemode
///// https://docs.microsoft.com/en-us/windows/console/readconsole
///// </summary>
//
//namespace dragon
//{
//
//	void WindowsConsoleWindow::ProcessEvents()
//	{
//
//	}
//
//	void* WindowsConsoleWindow::GetNativeWindowHandle() const
//	{
//		return GetConsoleWindow();
//	}
//
//	Vector2 WindowsConsoleWindow::GetPosition()
//	{
//		HWND handle = GetConsoleWindow();
//		tagRECT rect;
//		rect.left = 0;
//		rect.top = 0;
//		GetWindowRect(handle, &rect);
//		return Vector2(rect.left, rect.top);
//	}
//
//	Vector2 WindowsConsoleWindow::GetSize()
//	{
//		HWND handle = GetConsoleWindow();
//		tagRECT rect;
//		rect.left = 0;
//		rect.top = 0;
//		rect.bottom = 0;
//		rect.right = 0;
//		GetWindowRect(handle, &rect);
//		return Vector2(rect.right - rect.left, rect.bottom - rect.top);
//	}
//
//}