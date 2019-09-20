#pragma once

#include <Dragon/Math/MathDefinitions.h>
#include <Dragon/Graphics/RenderState.h>
#include <Dragon/Math/Math.h>

namespace dragon
{
	class Renderable;
	class Texture;

	class RenderTarget
	{
	private:
		Vector2f m_size;

	public:

		RenderTarget()
			: RenderTarget({1024.0f, 1024.0f})
		{}

		RenderTarget(Vector2f size)
			: m_size(size)
		{}

		~RenderTarget() = default;

		RenderTarget(const RenderTarget&) = default;
		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(const RenderTarget&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;

		Vector2f GetSize() const { return m_size; }
		void SetSize(Vector2f size) { m_size = size; OnResize(size); }

		void Draw(const Renderable& renderable, const RenderState& state = RenderState::Default);

		// Convenience Methods

		//void DrawTexture(const Texture& texture, RectF src = { 0.0f }, RectF dest = { 0.0f });
		
		//void DrawRect();
		//void DrawFillRect();

		//void DrawCircle();
		//void DrawFillCircle();

	protected:

		virtual void OnResize(Vector2f size) = 0;

	};
}