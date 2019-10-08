#pragma once

#include <EASTL/string.h>

namespace dragon
{

	class OutStream
	{
		using Byte = std::byte;

	public:

		// Raw Data
		virtual void Write(const Byte* data, size_t len) = 0;
		virtual void Write(const char* data, size_t len);
		virtual void Write(const unsigned char* data, size_t len);

		// Character/String
		void Write(const eastl::string& text);
		void Write(char character);

		// Numbers
		void Write(short num);
		void Write(int num);
		void Write(long long num);

		void Write(unsigned short num);
		void Write(unsigned int num);
		void Write(unsigned long long num);

		// Floating point types
		void Write(float num);
		void Write(double num);

		template<typename Type>
		void Write(const Type& val) { static_assert(__FILE__ ": Write<>(const Type& val) has not been overloaded for the given type."); }
	};

}