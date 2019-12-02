#include "OutStream.h"

#include <Dragon/Application/Debugging/Debug.h>

#include <fstream>

namespace dragon
{
	OutStream::OutStream(size_t count, Byte* data)
	{
	}

	OutStream::OutStream(const char* fileName)
	{
		std::ofstream* pFile = new std::ofstream();
		pFile->open(fileName, std::ios::binary | std::ios::out);
		m_pOutStream = pFile;
	}

	OutStream::~OutStream()
	{
		delete m_pOutStream;
	}

	void OutStream::Serialize(const Byte* data, size_t len)
	{
		if(Good())
			m_pOutStream->write(reinterpret_cast<const char*>(data), len);
	}

	void OutStream::Serialize(const char* data, size_t len)
	{
		if(Good())
			m_pOutStream->write(data, len);
	}

	void OutStream::Serialize(const unsigned char* data, size_t len)
	{
		Serialize(reinterpret_cast<const Byte*>(data), len);
	}

	void OutStream::Serialize(const eastl::string& text)
	{
		Serialize(text.length());
		Serialize(reinterpret_cast<const Byte*>(text.data()));
	}

	bool OutStream::Good() const
	{
		if (m_pOutStream->good())
		{
			return true;
		}
		else
		{
			DERR("Attempting to write to bad output stream.");
			return false;
		}
	}

}