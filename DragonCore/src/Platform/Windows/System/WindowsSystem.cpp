#include "WindowsSystem.h"

// Dragon Engine
#include <Dragon/Config.h>

// std
#include <iostream>

// Windows
#include <Windows.h>
#include <ShlObj_core.h>
#include <Shlwapi.h>

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

	//WindowsSystem::ConsoleColor WindowsSystem::ColorToConsoleColor(Color color)
	//{
	//	color.r = std::floor(color.r * 255);
	//	color.g = std::floor(color.g * 255);
	//	color.b = std::floor(color.b * 255);
	//	color.a = std::floor(color.a * 255);

	//	int index = ( (color.r > 128) | (color.g > 128) | (color.b > 128) ) ? 8 : 0; // Bright bit
	//	index |= (color.r > 64) ? 4 : 0; // Red bit
	//	index |= (color.g > 64) ? 2 : 0; // Green bit
	//	index |= (color.b > 64) ? 1 : 0; // Blue bit
	//	return (WindowsSystem::ConsoleColor)index;
	//}

}