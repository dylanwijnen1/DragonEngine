#pragma once

#include <Dragon/Config.h>
#include <Dragon/Generic/Math.h>

namespace sf
{
	class Texture;
}

namespace dragon
{
	class SfmlTexture
	{
		sf::Texture* m_pTexture;

	public:

		SfmlTexture() 
			: m_pTexture(nullptr)
		{}

		~SfmlTexture();

		// Wrap the texture into the implementation.
		SfmlTexture(sf::Texture* pTexture) 
			: m_pTexture(pTexture) 
		{}

		bool LoadFromFile(const char* filename);
		bool LoadFromMemory(const dragon::Byte* pData, size_t size);

		bool IsValid() const { return m_pTexture != nullptr; }
		void Destroy();

		Vector2f GetSize() const;

		sf::Texture* GetNativeTexture() const { return m_pTexture; }
	};

}