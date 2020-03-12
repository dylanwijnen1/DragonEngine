#pragma once

#include <Dragon/Config.h>
#include <Dragon/Debug.h>


#include <Dragon/Graphics/Color.h>
#include <Dragon/Graphics/PrimitiveType.h>
#include <Dragon/Graphics/Camera.h>

#include <Dragon/Generic/Math.h>

namespace dragon
{
	class Renderable;

	/// <summary>
	/// Abstract class, The RenderTarget is passed to Renderables and around the Engine for rendering to the target.
	/// The target may be a Window or a RenderTexture.
	/// </summary>
	class RenderTarget
	{
		Camera m_camera;

	public:

		RenderTarget() = default;
		~RenderTarget() = default;

		// We cannot determine if a copy of the render target is slow to copy this is dependent on each skin.
		RenderTarget(const RenderTarget&) = default;
		RenderTarget(RenderTarget&&) = default;
		RenderTarget& operator=(const RenderTarget&) = default;
		RenderTarget& operator=(RenderTarget&&) = default;

		/// <summary>
		/// Size of the RenderTarget
		/// </summary>
		/// <returns></returns>
		virtual Vector2f GetSize() const = 0;

		/// <summary>
		/// Clears the RenderTarget
		/// </summary>
		/// <param name="color"></param>
		virtual void Clear(Color color) = 0;

		/// <summary>
		/// Draws a renderable item to the screen
		/// </summary>
		/// <param name="renderable"></param>
		void Draw(Renderable& renderable);

		/// <summary>
		/// Draws Vertices to the RenderTarget 
		/// </summary>
		/// <param name="pVertices"></param>
		/// <param name="vertexCount"></param>
		virtual void Draw(Vertex* pVertices, size_t vertexCount, PrimitiveType primitiveType) = 0;

		/// <summary>
		/// Return the native skin implementation target.
		/// </summary>
		/// <returns></returns>
		virtual void* GetNativeTarget() = 0;

		/// <summary>
		/// Immediately casts the implemented target.
		/// </summary>
		template<typename TargetType>
		TargetType* GetNativeTarget()
		{
			return static_cast<TargetType>(GetNativeTarget());
		}
	};
}