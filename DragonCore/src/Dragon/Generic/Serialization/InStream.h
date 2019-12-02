#pragma once

#include <EASTL/string.h>
#include <EASTL/type_traits.h>
#include <iosfwd>

namespace dragon
{

	class InStream
	{
		using Byte = std::byte;
		std::istream* m_pInStream;

	public:

		InStream() = delete;
		InStream(std::istream* pStream) : m_pInStream(pStream) {}
		InStream(size_t count, Byte* data);
		InStream(const char* fileName);

		// Do not move and do not copy construct/assign.
		InStream(const InStream&) = delete;
		InStream(InStream&&) = delete;
		InStream& operator=(const InStream&) = delete;
		InStream& operator=(InStream&&) = delete;

		~InStream();

		virtual void Deserialize(Byte* out, size_t len);
		void Deserialize(char* out, size_t len);
		void Deserialize(unsigned char* out, size_t len);

		template<typename Type>
		Type Deserialize();

		template<typename Type>
		void Deserialize(Type* pVal) { static_assert(__FILE__ ": Deserialize<>(Type* pVal) has not been overloaded for the given type.") }

	private:
		bool Good();
	};

	template<typename Type>
	inline Type InStream::Deserialize()
	{
		if constexpr (eastl::is_integral_v<Type> || eastl::is_floating_point_v<Type>)
		{
			Type value;
			Deserialize(reinterpret_cast<Byte*>(&value), sizeof(Type));
			return value;
		}
		else
		{
			static_assert(__FILE__ ": Deserialize<Type>() has not been overloaded for the given type.");
		}
	}

	template<>
	inline eastl::string InStream::Deserialize()
	{
		unsigned int length = Deserialize<unsigned int>() + 1;		// Create buffer and account for the null terminator at the end.
		char* pBuffer = new char[length];
		eastl::string text(pBuffer);						// Delete buffer
		delete[] pBuffer;

		return text;
	}

	// TODO: Remove T and replace with InStream, Requires extra indirection due to some weird template stuff.
	template<typename T, typename RetType>
	struct is_deserializable
	{
		template<typename U, RetType(U::*)()> struct SFINAE {};
		template<typename U> constexpr static char Test(SFINAE<U, &U::Deserialize>*);
		template<typename U> constexpr static int Test(...);
		inline constexpr static bool value = sizeof(Test<T>(0)) == sizeof(char);
	};

	template<typename Type>
	constexpr bool is_deserializable_v = is_deserializable<InStream, Type>::value;

};