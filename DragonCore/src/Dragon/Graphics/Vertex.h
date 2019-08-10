#pragma once

#include <Dragon/Math/MathDefinitions.h>
#include <Dragon/Graphics/Color.h>

namespace dragon
{

	struct Vertex
	{
	public:
		Color color;
		Vector2f position;
		Vector2f uv;
	};

}