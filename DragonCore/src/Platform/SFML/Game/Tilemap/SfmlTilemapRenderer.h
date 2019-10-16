#pragma once

#include <Dragon/Game/Tilemap/TilemapRenderer.h>

namespace dragon
{
	class SfmlTilemapRenderer : public TilemapRenderer
	{
	public:
		// Inherited via TilemapRenderer
		virtual void Render(RenderTarget& target, const Tilemap& tilemap, const TileLayer& layer) final override;
	};
}

