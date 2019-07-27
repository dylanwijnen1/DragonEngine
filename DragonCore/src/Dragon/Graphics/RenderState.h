#pragma once

namespace dragon
{

	enum struct BlendMode
	{
		Alpha,
		Additive,
		Multiply,
		None
	};

	class Shader;
	class Texture;
	//class Transform;

	struct RenderState
	{
		class Shader* m_pShader;
		class Texture* m_pTexture;
		//Transform m_transform;
		BlendMode m_blendMode;

	public:
		RenderState()
			: m_pShader(nullptr)
			, m_pTexture(nullptr)
			//, m_transform(Transform::Identity())
			, m_blendMode(BlendMode::Alpha)
		{}

	};

}