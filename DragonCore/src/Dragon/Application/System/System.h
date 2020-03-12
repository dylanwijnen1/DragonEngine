#pragma once

#include <iomanip>

//#include <Dragon/Config.h>
#include <Dragon/Application/System/SystemInfo.h>

#include <EASTL/vector.h>
#include <EASTL/string.h>

namespace dragon
{

	/// <summary>
	/// TODO: Modify API, Basic/Commonly used FileSystem functions, Return C++17 structs instead of FileInfo ?
	/// </summary>
	template<class SystemImpl>
	class _System
	{
		SystemImpl m_impl;

	public:

		using FilePaths = eastl::vector<FilePath>;

		_System() : m_impl() {}

		// Moving or Copying System is silly.
		_System(const _System&) = delete;
		_System(_System&&) = delete;

		_System& operator=(const _System&) = delete;
		_System& operator=(_System&&) = delete;

		/// <summary>
		/// Allocate system resources, such as information about the current system.
		/// </summary>
		bool Init() { return m_impl.Init(); }

		/// <summary>
		/// For example on a WindowsSystem this should return ~"Windows"~ or even specifically ~"Windows 10"~
		/// </summary>
		constexpr const char* GetSystemName() const { return m_impl.GetSystemName(); }

		/// <summary>
		/// Return the available and total memory on the system.
		/// \see ISystem::MemoryInfo
		/// </summary>
		MemoryInfo GetMemoryInfo() const { return m_impl.GetMemoryInfo(); };

		/// <summary>
		/// Return the drive information for the drive path given.
		/// </summary>
		/// <param name="path"></param>
		/// <returns></returns>
		DriveInfo GetDriveInfo(const char* path) const;

		/// <summary>
		/// Return the total of available disk drive space this program is run from.
		/// </summary>
		/// <returns></returns>
		DriveInfo GetDriveInfo() const;

		/// <summary>
		/// Return the name of the cpu
		/// </summary>
		/// <returns>A string containing the name of the cpu</returns>
		eastl::string GetCpuId() const { return m_impl.GetCpuId(); }

		/// <summary>
		/// Gets the amount of physical hardware cores.
		/// </summary>
		size_t GetCpuCores() const { return (size_t)std::thread::hardware_concurrency(); }

		GpuInfo GetGpuInfo() const { return m_impl.GetGpuInfo(); }

		DisplayInfo GetDefaultDisplayDevice() const { return m_impl.GetDefaultDisplayDevice(); }
		eastl::vector<DisplayInfo> GetAvailableDisplayDevices() const { return m_impl.GetAvailableDisplayDevices(); }

		/// <summary>
		/// List files inside a given directory.
		/// </summary>
		/// <param name="pDir">Starting directory</param>
		/// <param name="depth">The maximum depth allowed to recurse into. Or -1 to recurse indefinitely.</param>
		/// <returns>A list of file paths</returns>
		FilePaths ListDirectory(const char* pDir, int depth = 0) const;
		
		FilePath GetUserDirectoryPath() const { return m_impl.GetUserDirectoryPath(); }

		FilePath GetCurrentWorkingDirectory() const;
		
		/// <summary>
		/// Gets the locale timestamp as a string.
		/// </summary>
		/// <returns></returns>
		eastl::string GetTimestamp() const;
	};

	template<typename SystemImpl>
	inline DriveInfo _System<SystemImpl>::GetDriveInfo(const char* path) const
	{
		DriveInfo driveInfo;

		std::error_code err;
		std::filesystem::space_info info = std::filesystem::space(path, err);

		if (err)
		{
			driveInfo.m_available = 0;
			driveInfo.m_total = 0;
		}
		else
		{
			driveInfo.m_available = (size_t)info.available;
			driveInfo.m_total = (size_t)info.capacity;
		}

		return driveInfo;
	}

	template<typename SystemImpl>
	inline DriveInfo _System<SystemImpl>::GetDriveInfo() const
	{
		return GetDriveInfo(GetCurrentWorkingDirectory().c_str());
	}

	template<typename SystemImpl>
	typename _System<SystemImpl>::FilePaths _System<SystemImpl>::ListDirectory(const char* pDir, int depth) const
	{
		FilePaths entries;

		using RecursiveDirIterator = std::filesystem::recursive_directory_iterator;
		using DirectoryEntry = std::filesystem::directory_entry;

		auto iterator = RecursiveDirIterator(pDir);

		for (const DirectoryEntry& entry : iterator)
		{
			if (depth != -1 && iterator.depth() > depth)
				iterator.pop();

			entries.emplace_back(info);
		}

		return entries;
	}

	template<typename SystemImpl>
	inline FilePath _System<SystemImpl>::GetCurrentWorkingDirectory() const
	{
		std::error_code err;
		FilePath path = std::filesystem::current_path(err);
		if (!err)
			return path;
		else
			return FilePath("Invalid Path");
	}

	template<typename SystemImpl>
	inline eastl::string _System<SystemImpl>::GetTimestamp() const
	{
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm now_tm = *std::localtime(&now_c);

		std::stringstream ss;
		ss << std::put_time("%c", &now_tm) << std::endl;
		return ss.str();
	}
};

#if _WIN32

#include <Platform/Windows/System/WindowsSystem.h>
namespace dragon
{
	using System = _System<WindowsSystem>;
}

#else
#error "Unsupported System"
#endif
