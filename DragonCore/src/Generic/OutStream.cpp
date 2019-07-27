#include "OutStream.h"

void OutStream::Write(const char* data, size_t len)
{
	Write(reinterpret_cast<const std::byte*>(data), len);
}

void OutStream::Write(const unsigned char* data, size_t len)
{
	Write(reinterpret_cast<const std::byte*>(data), len);
}

void OutStream::Write(const eastl::string& text)
{
	Write(text.length());
	Write(reinterpret_cast<const std::byte*>(text.data()));
}

void OutStream::Write(char character)
{
	Write(reinterpret_cast<const std::byte*>(&character), sizeof(char));
}

void OutStream::Write(short num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(short));
}

void OutStream::Write(int num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(int));
}

void OutStream::Write(long long num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(long long));
}

void OutStream::Write(unsigned short num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(unsigned long long));
}

void OutStream::Write(unsigned int num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(unsigned int));
}

void OutStream::Write(unsigned long long num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(unsigned long long));
}

void OutStream::Write(float num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(float));
}

void OutStream::Write(double num)
{
	Write(reinterpret_cast<const std::byte*>(&num), sizeof(double));
}
