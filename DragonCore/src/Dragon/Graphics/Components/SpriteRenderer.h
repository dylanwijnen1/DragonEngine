#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Graphics/Renderable.h>
#include <Dragon/Graphics/Vertex.h>
#include <Dragon/Math/Math.h>

namespace dragon
{

	class SpriteRenderer : public Component, public Renderable
	{
		class Texture* m_pTexture;
		//Transform m_transform; // Position, Size, Rotation
		Rect m_srcRect;

		Vertex m_vertices[4];

	public:
		COMPONENT_ID(SpriteRenderer)

		SpriteRenderer() = default;
		~SpriteRenderer() = default;

		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(SpriteRenderer&&) = default;
		SpriteRenderer& operator=(const SpriteRenderer&) = default;
		SpriteRenderer& operator=(SpriteRenderer&&) = default;

		void SetTexture(Texture* pTexture);

		void SetSourceRect(Rect rect) { m_srcRect = rect; }
		Rect GetSourceRect() const { return m_srcRect; }

		void SetColor(Color color);
		Color GetColor() const;
		
		//void SetPosition(Vector2f pos) { m_transform.SetPosition(pos); }
		//Vector2f GetPosition() const { return m_transform.GetPosition(); }

		//void SetRotation(float rotation) { m_transform.SetRotation(rotation); }
		//float GetRotation() const { return m_transform.GetRotation(); }

		//void SetScale(Vector2f scale) { m_transform.SetScale(scale); }
		//Vector2f GetScale() const { return m_transform.GetScale(); }

	protected:
		// Inherited via Drawable
		virtual void Render(const RenderTarget& target, const RenderState& state) const final override;
	};

}