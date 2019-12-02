#pragma once

#include <EASTL/string.h>
#include <iosfwd>

namespace dragon
{

	class OutStream
	{
		using Byte = std::byte;

		std::ostream* m_pOutStream;

	public:

		OutStream() = delete;
		OutStream(std::ostream* pStream) : m_pOutStream(pStream) {}
		OutStream(size_t count, Byte* data); // TODO: Write MemBuffer
		OutStream(const char* fileName);

		// Do not move and do not copy construct/assign.
		OutStream(const OutStream&) = delete;
		OutStream(OutStream&&) = delete;
		OutStream& operator=(const OutStream&) = delete;
		OutStream& operator=(OutStream&&) = delete;

		~OutStream();

		// Raw Data
		virtual void Serialize(const Byte* data, size_t len);
		void Serialize(const char* data, size_t len);
		void Serialize(const unsigned char* data, size_t len);

		// Character/String
		void Serialize(const eastl::string& text);

		template<typename Type>
		void Serialize(Type type)
		{
			if constexpr (eastl::is_integral_v<Type> || eastl::is_floating_point_v<Type>)
			{
				Serialize(reinterpret_cast<const Byte*>(&type), sizeof(Type));
			}
			else
			{
				static_assert(__FILE__ ": " __FUNCSIG__ " has not been overloaded for the given type.");
			}
		}

		//template<typename Type>
		//void Serialize(const Type& val) { static_assert(__FILE__ ": "__FUNCSIG__" has not been overloaded for the given type."); }

		template<typename Type>
		void Serialize(Type* pVal) { static_assert(__FILE__ ": " __FUNCSIG__ " has not been overloaded for the given type."); }

	private:
		bool Good() const;
	};

	// TODO: Remove T and replace with InStream, Requires extra indirection due to some weird template stuff.
	template<typename T, typename... Args>
	struct is_serializable
	{
		template<typename U, void(U::*)(Args...)> struct SFINAE {};
		template<typename U> constexpr static char Test(SFINAE<U, &U::Serialize>*);
		template<typename U> constexpr static int Test(...);
		inline constexpr static bool value = sizeof(Test<T>(0)) == sizeof(char);
	};

	template<typename Type>
	constexpr bool is_serializable_v = is_serializable<OutStream, Type>::value;
}