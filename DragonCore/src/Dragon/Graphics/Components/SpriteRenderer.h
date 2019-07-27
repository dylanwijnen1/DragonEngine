#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Graphics/Drawable.h>

namespace dragon
{

	class SpriteRenderer : public Component, public Drawable
	{
		class Texture* m_pTexture;
		//Transform m_transform; // Position, Size, Rotation
		Rect m_srcRect;

	public:
		COMPONENT_ID(SpriteRenderer)

		SpriteRenderer() = default;
		~SpriteRenderer() = default;

		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(SpriteRenderer&&) = default;
		SpriteRenderer& operator=(const SpriteRenderer&) = default;
		SpriteRenderer& operator=(SpriteRenderer&&) = default;

		void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
		//void SetTexture(const eastl::string& path);

		void SetSourceRect(Rect rect) { m_srcRect = rect; }
		Rect GetSourceRect() const { return m_srcRect; }
		
		//void SetPosition(Vector2f pos);
		//Vector2f GetPosition() const;

		//void SetRotation(float rotation);
		//float GetRotation() const;

		//void SetScale(Vector2f scale);
		//Vector2f GetScale() const;

	protected:
		// Inherited via Drawable
		virtual void Draw(RenderTarget& target, RenderState state) final override;
	};

}