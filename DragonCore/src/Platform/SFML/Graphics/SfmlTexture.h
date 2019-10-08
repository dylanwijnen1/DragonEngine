#pragma once

#include <Dragon/Config.h>
#include <Dragon/Generic/Math.h>

namespace sf
{
	class SfmlTexture
	{
		class Texture* m_pTexture;

	public:

		bool LoadFromFile(const char* filename);
		bool LoadFromMemory(const dragon::Byte* pData, size_t size);

		void Destroy();

		dragon::Vector2f GetSize() const;

		Texture* GetDeviceTexture() const { return m_pTexture; }
	};

}