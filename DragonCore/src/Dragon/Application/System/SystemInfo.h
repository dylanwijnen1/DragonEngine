#pragma once

#include <Dragon/Generic/Math.h>
#include <EASTL/string.h>

#include <filesystem>

namespace dragon
{
	using FilePath = std::filesystem::path;

	struct MemoryInfo
	{
		/// <summary>
		/// Total physical installed memory in KB
		/// </summary>
		size_t m_totalPhysical;

		/// <summary>
		/// Available physical memory in KB
		/// </summary>
		size_t m_availablePhysical;
	};

	struct DriveInfo
	{
		/// <summary>
		/// Total space of the drive in bytes.
		/// </summary>
		size_t m_total;

		/// <summary>
		/// Space available in bytes.
		/// </summary>
		size_t m_available;
	};

	struct GpuInfo
	{
		/// <summary>
		/// Available video ram.
		/// </summary>
		size_t m_availableVRam;

		/// <summary>
		/// Total video ram.
		/// </summary>
		size_t m_totalVRam;
	};

	struct DisplayInfo
	{
		/// <summary>
		/// The name of the device.
		/// </summary>
		eastl::string m_name;

		/// <summary>
		/// The size of the device in pixels.
		/// </summary>
		Vector2 m_size;

		/// <summary>
		/// Virtual display rectangle of the device.
		/// </summary>
		Rect m_virtualRect;
	};
}