#pragma once

#include <EASTL/vector.h>
#include <EASTL/string.h>

#include <Dragon/Graphics/Color.h>

namespace dragon
{
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

	struct GpuInfo
	{
		size_t m_availableVRam;
		size_t m_totalVRam;
	};

	struct FileInfo
	{
		eastl::string m_path; //FindPath + Relative
		eastl::string m_name; //Folder/FileName
		eastl::string m_extension; //Extension of the file. Empty when FileInfo m_isDir

		enum struct FileType
		{
			Folder,
			File,
			Unknown
		} m_type;

		unsigned long long m_size;
		unsigned long long m_lastModified;
	};

	class Window;

	class DragonSystem
	{
	public:
		// Remove all ctors/assignments this is a factory class.
		DragonSystem() = default;
		DragonSystem(const DragonSystem&) = delete;
		DragonSystem(DragonSystem&&) = delete;

		DragonSystem& operator=(const DragonSystem&) = delete;
		DragonSystem& operator=(DragonSystem&&) = delete;

		virtual ~DragonSystem() = default;

		/// <summary>
		/// Allocate system resources such as memory gather information about the current system.
		/// </summary>
		virtual bool Init() { return true; }

		/// <summary>
		/// For example on a WindowsSystem this should return ~"Windows"~ or even specifically ~"Windows 10"~
		/// </summary>
		virtual const char* GetSystemName() const = 0;

		/// <summary>
		/// Return the available and total memory on the system.
		/// \see ISystem::MemoryInfo
		/// </summary>
		virtual MemoryInfo GetSystemMemory() const = 0;

		/// <summary>
		/// Return the total of available disk drive space this program is run from.
		/// </summary>
		virtual size_t GetAvailableDriveSpace() const = 0;

		/// <summary>
		/// Return the name of the cpu
		/// </summary>
		/// <returns>A string containing the name of the cpu</returns>
		//virtual std::string GetCpuId() const = 0;

		/// <summary>
		/// Gets the amount of physical hardware cores.
		/// </summary>
		size_t GetCpuCores() const;

		virtual Window* CreateSystemWindow() = 0;

		//virtual DisplayInfo GetDefaultDisplayDevice() const = 0;
		//virtual std::vector<DisplayInfo> GetAvailableDisplayDevices() const = 0;

		//virtual GpuInfo GetGpuInfo() const = 0; //VRAM available, VRAM total, Cores?, Max Resolution, Min/Max refresh rate.

		eastl::vector<FileInfo> FindDirectory(const char* pDir, int depth = 0) const;
		
		virtual eastl::string GetUserDirectoryPath() const = 0;

		// TODO: Use std::chrono, https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
		virtual eastl::string GetTimestamp() const = 0;

		virtual void SetConsoleColor(Color color = Colors::White) = 0;

		static DragonSystem* Create();
			
	};

};
