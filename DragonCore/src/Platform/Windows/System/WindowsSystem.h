#pragma once

#include <Dragon/Application/System/DragonSystem.h>

namespace dragon
{

	class DragonWindow;

	class WindowsSystem final : public DragonSystem
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
		~WindowsSystem() { delete m_outHandle; m_outHandle = nullptr; }

		virtual const char * GetSystemName() const override { return "Windows"; };
		
		virtual bool Init() override;

		virtual MemoryInfo GetSystemMemory() const override;
		virtual size_t GetAvailableDriveSpace() const override;

		virtual eastl::string GetUserDirectoryPath() const override;

		// TODO: Possibly move to DragonSystem and use Chrono format.
		virtual eastl::string GetTimestamp() const override;

		virtual void SetConsoleColor(Color color) override;

		// Inherited via ISystem
		virtual DragonWindow* CreateSystemWindow() override;

	private:
		ConsoleColor ColorToConsoleColor(Color color);
	};

};