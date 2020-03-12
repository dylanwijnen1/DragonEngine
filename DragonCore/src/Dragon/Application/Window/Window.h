#pragma once

#include <Dragon/Config.h>
#include <Dragon/Generic/Math/Vector.h>

#include <Dragon/Graphics/RenderTarget.h>

#include <Dragon/Application/ApplicationEvent.h>

namespace dragon
{
	/// <summary>
	/// This is object creates the window for the current platform and owns the Keyboard and Mouse.
	/// </summary>				
	template<typename WindowImpl>
	class _Window : public RenderTarget
	{
		WindowImpl m_impl;

	public:

		_Window()
			: m_impl() 
		{}

		// Moving / Copying a window is silly.
		_Window(const _Window&) = delete;
		_Window(_Window&&) = delete;
		_Window& operator=(const _Window&) = delete;
		_Window& operator=(_Window&&) = delete;

		/// <summary>
		/// Initialize the window
		/// </summary>
		/// <param name="pTitle">The title of the window</param>
		/// <param name="width">Width of the window</param>
		/// <param name="height">Height of the window</param>
		/// <returns>If the window creation succeeded</returns>
		bool Init(const char* pTitle, size_t width, size_t height) { return m_impl.Init(pTitle, width, height); }

		/// <summary>
		/// Closes the window.
		/// </summary>
		void Close() { m_impl.Close(); }

		/// <summary>
		/// Returns wether the window has focus or not.
		/// </summary>
		/// <returns></returns>
		bool HasFocus() const { return m_impl.HasFocus(); }

		/// <summary>
		/// Process window events, Must be implemented by skin implementation
		/// </summary>
		void ProcessEvents() { m_impl.ProcessEvents(); };

		/// <summary>
		/// Return the native window handle
		/// This would be the ~HWND~ for a windows Window
		/// </summary>
		/// <returns></returns>
		void* GetNativeWindowHandle() const { return m_impl.GetNativeWindowHandle(); }

		template<typename NativeType>
		NativeType* GetNativeWindowHandle() const { return m_impl.GetNativeWindowHandle(); }

		/// <summary>
		/// Set the position of the window.
		/// </summary>
		/// <param name="x">The horizontal position to place the window at.</param>
		/// <param name="y">The vertical position to place the window at.</param>
		void SetWindowPosition(int x, int y) { m_impl.SetPosition(x, y); }

		/// <summary>
		/// Get the position of the window.
		/// </summary>
		/// <returns></returns>
		Vector2 GetWindowPosition() const { return m_impl.GetPosition(); }

		/// <summary>
		/// Set the size of the window.
		/// </summary>
		/// <param name="width">The width of the window.</param>
		/// <param name="height">The heigh of the window.</param>
		void SetWindowSize(size_t width, size_t height) { m_impl.SetWindowSize(width, height); }

		/// <summary>
		/// Get the size of the window.
		/// </summary>
		/// <returns></returns>
		Vector2 GetWindowSize() const { return m_impl.GetWindowSize(); }

		// Inherited via RenderTarget

		virtual Vector2f GetSize() const final override
		{
			Vector2 size = GetWindowSize();
			return Vector2f((float)size.x, (float)size.y);
		}

		/// <summary>
		/// Swap the graphical buffer for the window.
		/// </summary>
		void SwapBuffers() { m_impl.SwapBuffers(); }

		virtual void Clear(Color color) final override
		{
			m_impl.Clear(color);
		}

		virtual void Draw(Vertex* pVertices, size_t vertexCount, PrimitiveType primitiveType) final override
		{
			m_impl.Draw(pVertices, vertexCount, primitiveType);
		}

		virtual void* GetNativeTarget() final override
		{
			return m_impl.GetNativeTarget();
		}

	};

};

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML

#include <Platform/SFML/Window/SfmlWindow.h>
namespace dragon
{
	using Window = _Window<SfmlWindow>;
}

#elif DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_NONE

namespace dragon
{
	using Window = std::nullptr_t;
}

#else
#error "Unsupported Renderskin"
#endif