#pragma once

#include <EABase/int128.h>
#include <stdint.h>

namespace dragon
{

	struct Handle
	{
		inline constexpr static uint64_t kIdFlag = 0x000000FFFFFFFF;

		uint64_t m_handle;

	public:

		Handle(uint64_t id) : m_handle(id) {}

		size_t GetId() const { return (size_t)(m_handle & kIdFlag); }

		uint64_t GetVersion() const { return (uint64_t)(m_handle >> 32); }

		// TODO: Technically against GAP Standards. But don't wanna make a .cpp just for this line.
		uint64_t Increment() { m_handle &= kIdFlag; m_handle |= (GetVersion() + 1 << 32); return (uint64_t)m_handle; }

		bool IsValid() const { return GetVersion() != 0; }

		operator bool() const { return GetVersion() != 0; }

		operator size_t() const { return GetId(); }

		bool operator==(const Handle& other) const { return m_handle == other.m_handle; }
		bool operator!=(const Handle& other) const { return !(*this == other); }
	};

}

// custom specialization of std::hash can be injected in namespace std
namespace eastl
{
	template<> struct hash<dragon::Handle>
	{
		size_t operator()(dragon::Handle const& self) const noexcept
		{
			return self.GetId();
		}
	};
}