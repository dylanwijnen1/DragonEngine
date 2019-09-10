#pragma once

#include <Dragon/Math/MathDefinitions.h>
#include <Dragon/Graphics/Color.h>

namespace dragon
{

	enum struct VertexType
	{
		Points,
		Lines,
		LineLoop,
		LineStrip,
		Triangles,
		TriangleStrip,
		TriangleFan,
	};

	struct Vertex
	{
	public:
		Color color;
		Vector2f position;
		Vector2f uv;
	};

}