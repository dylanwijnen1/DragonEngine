#pragma once

#include <Dragon/Graphics/Components/RenderComponent.h>
#include <Dragon/Graphics/Color.h>
#include <Dragon/Math/Math.h>

namespace dragon
{
	class Sprite;
	class SpriteRenderer : public RenderComponent
	{
		Sprite* m_pSprite;

	public:
		COMPONENT_ID(SpriteRenderer)

		SpriteRenderer() = default;
		~SpriteRenderer() = default;

		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(SpriteRenderer&&) = default;
		SpriteRenderer& operator=(const SpriteRenderer&) = default;
		SpriteRenderer& operator=(SpriteRenderer&&) = default;

		//void SetTexture(Texture* pTexture);

		//void SetSourceRect(Rect rect);
		//Rect GetSourceRect() const;

		//void SetColor(Color color);
		//Color GetColor() const;
		
		//void SetPosition(Vector2f pos);
		//Vector2f GetPosition() const;

		//void SetRotation(float rotation);
		//float GetRotation() const;

		//void SetScale(Vector2f scale);
		//Vector2f GetScale() const;

	protected:
		// Inherited via RenderComponent
		virtual void Render(RenderTarget& target, RenderState state) const override;
	};

}