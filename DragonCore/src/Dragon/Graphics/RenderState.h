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
		class Shader* pShader;
		class Texture* pTexture;
		//Transform transform;
		BlendMode blendMode;
		//Camera camera;

	public:

		static const RenderState Default;

		RenderState()
			: pShader(nullptr)
			, pTexture(nullptr)
			//, m_transform(Transform::Identity())
			, blendMode(BlendMode::Alpha)
		{}

	};

	inline const RenderState RenderState::Default = RenderState();

}