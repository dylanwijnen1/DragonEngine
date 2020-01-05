#pragma once

#include <Dragon/Config.h>

#include <EASTL/type_traits.h>

namespace dragon
{
	template<typename Type>
	struct StreamReader
	{
		Type Read(class InStream& in)
		{
			static_assert(false, "Read has not been specialized for the given type. " __FILE__ ", Line: " STRINGIFY(__LINE__));
		}
	};

	class InStream
	{
	public:
		virtual void Read(Byte* out, size_t len) = 0;
		void Read(char* out, size_t len);
		void Read(unsigned char* out, size_t len);

		template<typename Type>
		Type Read()
		{
			if constexpr (eastl::is_arithmetic_v<Type> || eastl::is_enum_v<Type>)
			{
				Type value;
				Read(reinterpret_cast<Byte*>(&value), sizeof(Type));
				return value;
			}
			else
			{
				return StreamReader<Type>().Read(*this);
			}
		}

	};

	//template<>
	//struct StreamReader<eastl::string>
	//{
	//	eastl::string Read(InStream& in)
	//	{
	//		// Read length of string.
	//		unsigned int length = in.Read<unsigned int>();

	//		// Create buffer and account for the null terminator at the end.
	//		char* pBuffer = new char[length + 1];

	//		// Read the characters.
	//		in.Read(pBuffer, length);

	//		// Create the string.
	//		eastl::string text(pBuffer);

	//		// Delete buffer
	//		delete[] pBuffer;

	//		return text;
	//	}
	//};

}