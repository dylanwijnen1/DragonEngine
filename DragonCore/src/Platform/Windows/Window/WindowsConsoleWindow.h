#pragma once

#include <Dragon/Application/Window/Window.h>

namespace dragon
{
	class WindowsConsoleWindow : public Window
	{
		// Inherited via Window
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