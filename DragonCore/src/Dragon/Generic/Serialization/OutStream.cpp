#include "OutStream.h"

namespace dragon
{

	void OutStream::Write(const char* data, size_t len)
	{
		Write(reinterpret_cast<const Byte*>(data), len);
	}

	void OutStream::Write(const unsigned char* data, size_t len)
	{
		Write(reinterpret_cast<const Byte*>(data), len);
	}

}