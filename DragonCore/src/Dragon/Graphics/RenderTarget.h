#pragma once

#include <Dragon/Config.h>

#include <Dragon/Graphics/Color.h>
#include <Dragon/Graphics/Camera.h>
#include <Dragon/Generic/Math.h>

namespace dragon
{
	class Renderable;

	class RenderTarget
	{
		Vector2f m_size;
		Camera m_camera;

	public:
		RenderTarget() = default;
		~RenderTarget() = default;

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget(RenderTarget&&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;
		RenderTarget& operator=(RenderTarget&&) = delete;

		// Implementation Defined Functions
		virtual bool Init(Vector2f size) { m_size = size; return true; }

		virtual Vector2f GetSize() const { return m_size; }
		virtual void SetSize(Vector2f size) { m_size = size; OnSizeChanged(size); }

		virtual void Clear(Color color) = 0;

		void SetCamera(Camera camera) { m_camera = camera; OnCameraChanged(camera); }
		Camera GetCamera() const { return m_camera; }

		void Draw(Renderable& renderable);

	protected:

		virtual void OnSizeChanged(Vector2f size) {}
		virtual void OnCameraChanged(Camera camera) {}

		// TODO:
		// Convenience Methods

		//void DrawTexture(const Texture& texture, RectF src = { 0.0f }, RectF dest = { 0.0f });
		
		//void DrawRect(RectF rect, Color color);
		//void DrawFillRect(RectF rect, Color color, Color fillColor = color, float thickness = 1.0f) { m_impl.DrawFillRect(rect, color, fillColor, thickness); }

		//void DrawCircle(Vector2f position, float radius, Color color) { m_impl.DrawCircle(position, radius, color); }
		//void DrawFillCircle(Vector2f position, float radius, Color color, Color fillColor = color, float thickness = 1.0f) { m_impl.DrawFillCircle(position, radius, color, fillColor, thickness); }
	};
}