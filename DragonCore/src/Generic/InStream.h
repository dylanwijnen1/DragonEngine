#pragma once

#include <EASTL/string.h>
#include <EASTL/type_traits.h>

class InStream
{
	using Byte = std::byte;

public:
	virtual void Read(Byte* out, size_t len) = 0;
	void Read(char* out, size_t len);
	void Read(unsigned char* out, size_t len);

	template<typename Type>
	Type Read();

	template<typename Type>
	void Read(Type* pVal) { static_assert(__FILE__ ": Read<>(Type* pVal) has not been overloaded for the given type.") }
};

template<typename Type>
inline Type InStream::Read()
{
	if constexpr (eastl::is_integral_v<Type> || eastl::is_floating_point_v<Type>)
	{
		Type value;
		Read(reinterpret_cast<Byte*>(&value), sizeof(Type));
		return value;
	}
	else
	{
		static_assert(__FILE__ ": Read<Type>() has not been overloaded for the given type.");
	}
}

template<>
inline eastl::string InStream::Read() 
{
	unsigned int length = Read<unsigned int>() + 1;		// Create buffer and account for the null terminator at the end.
	char* pBuffer = new char[length];					
	eastl::string text(pBuffer);						// Delete buffer
	delete[] pBuffer;

	return text;
}

