#pragma once

#include <Dragon/Config.h>

#include <Dragon/Graphics/Color.h>
#include <Dragon/Graphics/Camera.h>
#include <Dragon/Generic/Math.h>

namespace dragon
{
	class Renderable;

	/// <summary>
	/// Abstract class, The RenderTarget is passed to Renderables and around the Engine for rendering to the target.
	/// The target may be a Backbuffer or a RenderTexture.
	/// </summary>
	class RenderTarget
	{
	public:
		RenderTarget() = default;
		~RenderTarget() = default;

		// We cannot determine if a copy of the render target is slow to copy. It might be fast. So we open the interface up for these situations.
		// This might change.
		RenderTarget(const RenderTarget&) = default;
		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(const RenderTarget&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;

		/// <summary>
		/// Initialize the RenderTarget
		/// </summary>
		/// <param name="size"></param>
		/// <returns></returns>
		virtual bool Init(Vector2f size) = 0;

		virtual Vector2f GetSize() const = 0;
		virtual void SetSize(Vector2f size) = 0;

		virtual void Clear(Color color) = 0;

		virtual void SetCamera(Camera camera) = 0;
		virtual Camera GetCamera() const = 0;

		/// <summary>
		/// Return the native skin implementation target.
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeTarget() = 0;

		// Drawing Entities

		void Draw(Renderable& renderable);

		// Convenience Methods, Mainly used for debugging

		virtual void DrawRect(RectF rect, Color color) {}
		virtual void DrawFillRect(RectF rect, Color color, Color outlineColor, float outlineSize) {}

		virtual void DrawCircle(Vector2f pos, float radius, Color color) {}
		virtual void DrawCircle(Vector2f pos, float radius, Color color, Color outlineColor, float outlineSize) {}
	};
}