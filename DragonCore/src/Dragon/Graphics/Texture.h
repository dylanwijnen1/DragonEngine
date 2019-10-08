#pragma once

#include <Dragon/Config.h>
#include <Dragon/Math/Math.h>

namespace dragon
{
	template<typename Impl>
	class _Texture
	{
		Impl m_impl;

	public:
		_Texture() = default;
		~_Texture() = default;

		// Copying is bad, Moving is ok!
		_Texture(const _Texture&) = delete;
		_Texture(_Texture&&) = default;
		_Texture& operator=(const _Texture&) = delete;
		_Texture& operator=(_Texture&&) = default;

		/// <summary>
		/// Load a texture from a filepath.
		/// </summary>
		/// <param name="filename"></param>
		/// <returns>Wether or not the file has been loaded.</returns>
		bool LoadFromFile(const char* filename) { return m_impl.LoadFromFile(filename); }

		/// <summary>
		/// Load a texture from raw memory.
		/// </summary>
		/// <param name="pRawData"></param>
		/// <param name="size">Size of the raw data.</param>
		/// <returns>Wether the texture was loaded correctly.</returns>
		bool LoadFromMemory(const Byte* pData, size_t size) { return m_impl.LoadFromMemory(pData, size); }

		/// <summary>
		/// Destroy the texture.
		/// </summary>
		void Destroy() { m_impl.Destroy(); }

		/// <summary>
		/// Get the size of this texture.
		/// </summary>
		dragon::Vector2f GetSize() const { return m_impl.GetSize(); }

		/// <summary>
		/// Get the implementation texture.
		/// </summary>
		const Impl& GetImplTexture() const { return m_impl; }

		/// <summary>
		/// Get the implementation texture.
		/// </summary>
		/// <returns></returns>
		Impl& GetImplTexture() { return m_impl; }

		/// <summary>
		/// Raw pointer to the device texture.
		/// </summary>
		/// <returns></returns>
		void* GetDeviceTexture() const { return m_impl.GetDeviceTexture(); }
	};

}

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML

#include <Platform/SFML/Graphics/SfmlTexture.h>

namespace dragon
{
	using Texture = _Texture<sf::SfmlTexture>;
}

#endif