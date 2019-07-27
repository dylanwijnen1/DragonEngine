#pragma once

#include <Dragon/Application/Window/DragonWindow.h>

namespace dragon
{
	class WindowsConsoleWindow : public DragonWindow
	{
		// Inherited via DragonWindow
		virtual bool Init(const char* pTitle, size_t width, size_t height) { return true; }
		virtual void Close() override {}
		virtual void ProcessEvents() override; // Take Input ?
		virtual void* GetNativeWindowHandle() const override;
		virtual void SwapBuffers() override {}
		virtual void SetPosition(int x, int y) override {}
		virtual Vector2 GetPosition() override;
		virtual void SetSize(size_t width, size_t height) override {}
		virtual Vector2 GetSize() override;
	};
}