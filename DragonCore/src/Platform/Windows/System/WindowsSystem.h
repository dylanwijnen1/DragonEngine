#pragma once

#include <Dragon/Config.h>
#include <Dragon/Application/System/SystemInfo.h>

namespace dragon
{
	class WindowsSystem
	{
		enum struct ConsoleColor : uint8_t
		{
			kBlack,
			kDarkBlue,
			kDarkGreen,
			kDarkCyan,
			kDarkRed,
			kDarkMagenta,
			kDarkYellow,
			kGray,
			kDarkGray,
			kBlue,
			kGreen,
			kCyan,
			kRed,
			kMagenta,
			kYellow,
			kWhite,
		};

		void* m_outHandle;

	public:
		WindowsSystem() : m_outHandle(nullptr) {}

		WindowsSystem(const WindowsSystem&) = delete;
		WindowsSystem(WindowsSystem&&) = delete;
		WindowsSystem& operator=(const WindowsSystem&) = delete;
		WindowsSystem& operator=(WindowsSystem&&) = delete;

		~WindowsSystem() { m_outHandle = nullptr; }

		bool Init();

		constexpr const char* GetSystemName() const { return "Windows"; };

		MemoryInfo GetSystemMemory() const;

	private:
		//ConsoleColor ColorToConsoleColor(Color color);
	};

};