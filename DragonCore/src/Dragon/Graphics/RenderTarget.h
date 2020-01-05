#pragma once

#include <Dragon/Config.h>
#include <Dragon/Debug.h>


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
		Vector2f m_size;
		Camera m_camera;

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
		virtual bool Init(Vector2f size);

		Vector2f GetSize() const { return m_size; }
		void SetSize(Vector2f size) { m_size = size; OnSizeChanged(size); }

		virtual void Clear(Color color) = 0;

		virtual Camera GetCamera() const { return m_camera; }
		void SetCamera(Camera camera) { m_camera = camera; OnCameraChanged(camera); }
		Camera GetDefaultCamera() const { return { m_size / 2.f, m_size, { 0.f, 0.f, 1.f, 1.f } }; }

		/// <summary>
		/// Return the native skin implementation target.
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeTarget() = 0;

		template<typename TargetType>
		TargetType GetNativeTarget()
		{
			return static_cast<TargetType>(GetNativeTarget());
		}

		// Drawing Entities
		void Draw(Renderable& renderable);

		// Convenience Methods, Mainly used for debugging
		virtual void DrawRect(RectF rect, Color color) { DWARN("RenderTarget::DrawRect not available for this target."); }
		virtual void DrawFillRect(RectF rect, Color color, Color outlineColor, float outlineSize) { DWARN("RenderTarget::DrawFillRect not available for this target."); }

		virtual void DrawCircle(Vector2f pos, float radius, Color color) { DWARN("RenderTarget::DrawCircle not available for this target."); }
		virtual void DrawFillCircle(Vector2f pos, float radius, Color color, Color outlineColor, float outlineSize) { DWARN("RenderTarget::DrawFillCircle not available for this target."); }

	protected:

		virtual void OnSizeChanged(Vector2f size) {}
		virtual void OnCameraChanged(Camera camera) {}
	};
}