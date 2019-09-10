#pragma once

#include <Dragon/Game/Component.h>
#include <Dragon/Graphics/Renderable.h>

namespace dragon
{

	class RenderComponent : public Component, public Renderable
	{
	public:

		// Component

		static constexpr ComponentId Identifier = "RenderComponent"_hash64;
		virtual ComponentId GetIdentifier() const override { return Identifier; }
		virtual Component* Clone() const override = 0;

		virtual bool Init() override;

		// Renderable

		virtual void Render(RenderTarget& target) = 0;
	};

}