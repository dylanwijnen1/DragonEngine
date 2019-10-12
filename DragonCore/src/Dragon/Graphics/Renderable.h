#pragma once

namespace dragon
{

	class Renderable
	{
	public:
		virtual void Render(class RenderTarget& target) = 0;
	};

}