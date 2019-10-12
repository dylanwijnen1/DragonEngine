#include "WindowsSystem.h"

#include <Dragon/Config.h>

#include <Windows.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>

#include <iostream>

#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_NONE
	#include <Platform/Windows/Window/WindowsConsoleWindow.h>
#elif DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
	#include <Platform/SFML/Window/SfmlWindow.h>
#endif


namespace dragon
{
	bool WindowsSystem::Init()
	{
		m_outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!m_outHandle)
			return false;

		return true;
	}

	MemoryInfo WindowsSystem::GetSystemMemory() const
	{
		MEMORYSTATUSEX buffer;
		buffer.dwLength = sizeof(buffer); //For some reason you need to set this field inorder for it to work.

		if(GlobalMemoryStatusEx(&buffer) == 0)
		{
			//Failed to get memory info.
			//Debug::Error("Windows", "GlobalMemoryStatusEx, Func: %s Line: %d Error: %d", __FUNCTION__, __LINE__, GetLastError());
		}
	
		//Convert to KB and return SystemMemoryInfo.
		return { (size_t)(buffer.ullTotalPhys / 1024), (size_t)(buffer.ullAvailPhys / 1024) };
	}

	size_t WindowsSystem::GetAvailableDriveSpace() const
	{
		ULARGE_INTEGER diskSpace;
		if(GetDiskFreeSpaceEx(nullptr, nullptr, nullptr, &diskSpace) == 0)
		{
			//Debug::Warning("Windows", "Could not retrieve information on disk.");
		}

		return (size_t)(diskSpace.QuadPart / 1024);
	}

	eastl::string WindowsSystem::GetUserDirectoryPath() const
	{
		PWSTR userDir = nullptr;

		if(!SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &userDir)))
		{
			//Incase the call fails we return an empty string.
			return "";
		}
		else
		{
			//Convert wchar to multibyte string.
			size_t len = wcslen(userDir);
			char* buffer = new char[len + 1];
			size_t converted = 0;
			wcstombs_s(&converted, buffer, 1 + sizeof(char) * len, userDir, sizeof(wchar_t) * len);

			eastl::string path(buffer);
			delete[] buffer;
			return path;
		}
	}

	eastl::string WindowsSystem::GetTimestamp() const
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);

		//eastl::string timeStamp;
		//timeStamp.sprintf("[%02d:%02d:%02d.%03d]", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

		char buffer[255];
		sprintf_s(buffer, 255, "[%02d:%02d:%02d]", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		eastl::string timeStamp(buffer);

		return timeStamp;
	}

	void WindowsSystem::SetConsoleColor(Color color)
	{
		if (m_outHandle)
		{
			SetConsoleTextAttribute(m_outHandle, (WORD)ColorToConsoleColor(color));
		}
	}

	Window* WindowsSystem::CreateSystemWindow()
	{
#if DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_SFML
		return new SfmlWindow();
#elif DRAGON_RENDERSKIN == DRAGON_RENDERSKIN_NONE
		return new WindowsConsoleWindow();
#else
	#error Invalid Renderskin, Not supported by Windows. 
#endif
	}

	WindowsSystem::ConsoleColor WindowsSystem::ColorToConsoleColor(Color color)
	{
		color.r = std::floor(color.r * 255);
		color.g = std::floor(color.g * 255);
		color.b = std::floor(color.b * 255);
		color.a = std::floor(color.a * 255);

		int index = ( (color.r > 128) | (color.g > 128) | (color.b > 128) ) ? 8 : 0; // Bright bit
		index |= (color.r > 64) ? 4 : 0; // Red bit
		index |= (color.g > 64) ? 2 : 0; // Green bit
		index |= (color.b > 64) ? 1 : 0; // Blue bit
		return (WindowsSystem::ConsoleColor)index;
	}

}