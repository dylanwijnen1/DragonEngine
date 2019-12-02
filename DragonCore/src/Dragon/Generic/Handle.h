#pragma once

#include <stdint.h>

#include <EASTL/functional.h>
#include <EASTL/type_traits.h>

#include <Dragon/Generic/Serialization/InStream.h>
#include <Dragon/Generic/Serialization/OutStream.h>

namespace dragon
{

	template<typename SizeType>
	struct Handle
	{
		static_assert(eastl::is_unsigned_v<SizeType>, "Handle size-type must be unsigned.");

		constexpr static SizeType kMax = eastl::numeric_limits<SizeType>::max();

		constexpr static size_t kHalfSize = sizeof(SizeType) * 4;
		constexpr static SizeType kClearIdFlag = kMax >> kHalfSize;
		constexpr static SizeType kInvalidVersionFlag = kClearIdFlag;

		inline constexpr static SizeType Invalid = kMax;

		SizeType m_handle;

		constexpr Handle() : m_handle(0) { }
		constexpr Handle(SizeType id) : m_handle(id) {}

		constexpr void SetId(SizeType id)
		{
			SizeType version = GetVersion();
			this->m_handle = id;
			SetVersion(version);
		}

		constexpr SizeType GetId() const { return (SizeType)(m_handle & kClearIdFlag); }

		constexpr void SetVersion(SizeType version)
		{
			m_handle &= kClearIdFlag; // Clear Version
			m_handle |= ((SizeType)version << kHalfSize); // Set Version 
		}

		constexpr SizeType GetVersion() const { return (SizeType)(m_handle >> kHalfSize); }
		
		constexpr void Increment()
		{ 
			SizeType version = GetVersion();
			SetVersion(++version);
		}

		constexpr bool IsValid() const { return GetVersion() != kInvalidVersionFlag; }
		constexpr void Invalidate() { SetVersion(kInvalidVersionFlag); }

		constexpr operator bool() const { return IsValid(); }

		constexpr bool operator==(const Handle& other) const { return m_handle == other.m_handle; }
		constexpr bool operator!=(const Handle& other) const { return !(*this == other); }
	};


}

// Custom specialization of hash.
namespace eastl
{
	template<typename SizeType>
	struct hash<dragon::Handle<SizeType>>
	{
		size_t operator()(const dragon::Handle<SizeType>& self) const noexcept
		{
			return (size_t)self.GetId();
		}
	};
}