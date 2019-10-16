#pragma once

#include <Dragon/Generic/Math.h>

namespace dragon
{
	// TODO: Instead of using these values to create a camera on for the platform.
	//	     This should actually be a matrix implementation so we can transform coordinates with the camera.
	//		 E.g : Vector2f worldPosition = Camera::ScreenToWorld(mousePosition);
	struct Camera
	{
	public:
		Camera()
			: Camera({ 0.f, 0.f }, { 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f })
		{}

		Camera(Vector2f pos, Vector2f size, RectF viewport) 
			: m_position(pos)
			, m_size(size)
			, m_viewport(viewport)
		{}

		Vector2f m_position;
		Vector2f m_size;
		RectF m_viewport;

		RectF GetViewBounds() const
		{
			Vector2f topLeft = m_position - (m_size / 2.0f);
			return { topLeft, m_size };
		}
	};

}