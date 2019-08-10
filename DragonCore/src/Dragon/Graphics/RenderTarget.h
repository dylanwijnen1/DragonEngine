#pragma once

#include <Dragon/Math/MathDefinitions.h>

namespace dragon
{
	class Drawable;
	class Texture;

	class Vertex;
	class VertexBuffer;
	class VertexArray;

	class RenderTarget
	{
		RenderState m_renderState;

	public:
		RenderTarget() = default;
		~RenderTarget() = default;

		RenderTarget(const RenderTarget&) = default;
		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(const RenderTarget&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;

		void Draw(const Drawable& drawable) const;

		void Draw(const VertexArray& data) const;
		void Draw(const VertexBuffer& buffer) const;
		void Draw(Vertex* vertices) const;

		// Convenience Methods

		void RenderTexture(const Texture* pTexture, RectF src = { 0.f }, RectF dest = { 0.0f });

	};
}