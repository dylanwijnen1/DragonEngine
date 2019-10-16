#pragma once

namespace dragon
{
	class TilemapRenderer
	{
	public:
		virtual void Render(class RenderTarget& target, const class Tilemap& tilemap, const struct TileLayer& layer) = 0;
	};
}