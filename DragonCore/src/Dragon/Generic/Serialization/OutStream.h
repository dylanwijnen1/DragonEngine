#pragma once

#include <Dragon/Config.h>

#include <EASTL/type_traits.h>

namespace dragon
{

	template<typename Type>
	struct StreamWriter
	{
		void Write(class OutStream& out, Type val)
		{
			static_assert(false, "Write has not been specialized for the given type. " __FILE__ ", Line: " STRINGIFY(__LINE__));
		}
	};

	class OutStream
	{
	public:

		// Raw Data
		virtual void Write(const Byte* data, size_t len) = 0;
		virtual void Write(const char* data, size_t len);
		virtual void Write(const unsigned char* data, size_t len);

		template<typename Type>
		void Write(Type val) 
		{
			// If the given type is numeric, write raw bytes.
			if constexpr (eastl::is_arithmetic_v<Type> || eastl::is_enum_v<Type>)
			{
				Write(reinterpret_cast<const Byte*>(&val), sizeof(Type));
			}
			else
			{
				// Write the data to the output stream.
				StreamWriter<Type>().Write(*this, val);
			}
		}
	};

}