#pragma once

#include <Dragon/Math/MathDefinitions.h>
#include <Dragon/Graphics/RenderState.h>
#include <Dragon/Graphics/Vertex.h>
#include <Dragon/Math/Math.h>

namespace dragon
{
	class Renderable;
	class Texture;

	class VertexBuffer;
	class VertexArray;

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

		void Draw(const Renderable& renderable, const RenderState& state = RenderState::Default);

		virtual void Draw(const VertexArray& data, const RenderState& state = RenderState::Default) = 0;
		virtual void Draw(const VertexBuffer& buffer, const RenderState& state = RenderState::Default) = 0;
		virtual void Draw(Vertex* vertices, size_t len, VertexType type, const RenderState& state = RenderState::Default) = 0;

		// Convenience Methods

		void DrawTexture(const Texture* pTexture, RectF src = { 0.0f }, RectF dest = { 0.0f });
		
		//void DrawRect();
		//void DrawFillRect();

		//void DrawCircle();
		//void DrawFillCircle();

	};
}