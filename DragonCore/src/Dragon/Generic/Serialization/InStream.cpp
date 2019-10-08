#include "InStream.h"

namespace dragon
{

	void InStream::Read(char* out, size_t len)
	{
		Read(reinterpret_cast<Byte*>(out), len);
	}

	void InStream::Read(unsigned char* out, size_t len)
	{
		Read(reinterpret_cast<Byte*>(out), len);
	}

}
