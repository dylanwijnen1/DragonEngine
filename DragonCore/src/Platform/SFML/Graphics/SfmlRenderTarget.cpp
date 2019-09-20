#include "SfmlRenderTarget.h"

#include <SFML/Graphics/VertexBuffer.hpp>

namespace dragon
{
	sf::Vector2u SfmlRenderTarget::getSize() const
	{
		Vector2f size = GetSize();
		return sf::Vector2u((sf::Uint32)size.x, (sf::Uint32)size.y);
	}

	//sf::RenderStates SfmlRenderTarget::ConvertState(const RenderState& state) const
	//{
	//	sf::RenderStates states;

	//	//states.texture = state.pTexture->GetNativeTexture();

	//	return states;
	//}

}