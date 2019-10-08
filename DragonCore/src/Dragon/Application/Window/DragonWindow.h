#pragma once

#include <Dragon/Generic/Math.h>
#include <Dragon/Application/ApplicationEvent.h>
#include <Dragon/Application/Input/Key.h>
#include <Dragon/Application/Input/MouseButton.h>

#include <EASTL/functional.h>

namespace dragon
{
	class DragonGraphics;

	/// \class DragonWindow
	/// <summary>
	/// This is object creates the window for the current platform and owns the Keyboard and Mouse.
	/// </summary>				
	class DragonWindow
	{
	public:
		using ApplicationEventCallback = eastl::function<void(ApplicationEvent&)>;

	protected:
		bool m_hasFocus;
		ApplicationEventCallback m_callback;

	public:
		DragonWindow() = default;
		virtual ~DragonWindow() = default;

		/// <summary>
		/// Initialize the window
		/// </summary>
		/// <param name="pTitle">The title of the window</param>
		/// <param name="width">Width of the window</param>
		/// <param name="height">Height of the window</param>
		/// <returns>If the window creation succeeded</returns>
		virtual bool Init(const char* pTitle, size_t width, size_t height) = 0;

		virtual void Close() = 0;

		/// <summary>
		/// Returns wether the window has focus or not.
		/// </summary>
		/// <returns></returns>
		bool HasFocus() { return m_hasFocus; }

		/// <summary>
		/// Process window events
		/// </summary>
		virtual void ProcessEvents() = 0;

		/// <summary>
		/// Set the callback function for the window. This is usually the application, which then dispatches it to all the layers.
		/// </summary>
		void SetEventCallback(const ApplicationEventCallback& callback) { m_callback = callback; }

		/// <summary>
		/// Return the native window handle
		/// This would be the ~HWND~ for a windows Window
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeWindowHandle() const = 0;

		/// <summary>
		/// Swap the graphical buffer for the window.
		/// </summary>
		virtual void SwapBuffers() = 0;

		/// <summary>
		/// Set the position of the window.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		virtual void SetPosition(int x, int y) = 0;

		/// <summary>
		/// Get the position of the window.
		/// </summary>
		/// <returns></returns>
		virtual Vector2 GetPosition() = 0;

		/// <summary>
		/// Set the size of the window.
		/// </summary>
		/// <param name="width"></param>
		/// <param name="height"></param>
		virtual void SetSize(size_t width, size_t height) = 0;

		/// <summary>
		/// Get the size of the window.
		/// </summary>
		/// <returns></returns>
		virtual Vector2 GetSize() = 0;

		DragonGraphics* CreateGraphics();
	};

};