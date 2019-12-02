#include "InStream.h"

#include <Dragon/Application/Debugging/Debug.h>

#include <fstream>

namespace dragon
{
	InStream::InStream(size_t count, Byte* data)
	{
		// TODO: Create a InStreamBuffer
	}

	InStream::InStream(const char* fileName)
	{
		std::ifstream* pFile = new std::ifstream();
		pFile->open(fileName, std::ios::binary | std::ios::in);
		m_pInStream = pFile;
	}

	InStream::~InStream()
	{
		delete m_pInStream;
		m_pInStream = nullptr;
	}

	void InStream::Deserialize(Byte* out, size_t len)
	{
		if(Good())
			m_pInStream->read(reinterpret_cast<char*>(out), len);
	}

	void InStream::Deserialize(char* out, size_t len)
	{
		if(Good())
			m_pInStream->read(out, len);
	}

	void InStream::Deserialize(unsigned char* out, size_t len)
	{
		Deserialize(reinterpret_cast<char*>(out), len);
	}

	bool InStream::Good()
	{
		if (!m_pInStream->good())
		{
			DERR("Attempting to read past stream size.");
			return false;
		}
		else
		{
			return true;
		}
	}

}
