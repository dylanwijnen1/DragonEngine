#include "DragonSystem.h"

#include <thread>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include <Platform/Windows/System/WindowsSystem.h>
#endif

namespace dragon
{
	size_t DragonSystem::GetCpuCores() const
	{
		return (size_t)std::thread::hardware_concurrency();
	}

	eastl::vector<FileInfo> DragonSystem::FindDirectory(const char* pDir, int depth) const
	{
		eastl::vector<FileInfo> entries;

		using RecursiveDirIterator = std::filesystem::recursive_directory_iterator;
		using DirectoryEntry = std::filesystem::directory_entry;

		auto iterator = RecursiveDirIterator(pDir);

		for (const DirectoryEntry& entry : iterator)
		{

			if (iterator.depth() > depth)
				iterator.pop();

			FileInfo info;
			auto path = entry.path();

			info.m_lastModified = entry.last_write_time().time_since_epoch().count();
			info.m_extension = path.extension().string().c_str();
			info.m_path = path.string().c_str();
			info.m_name = path.filename().string().c_str();
			info.m_size = (unsigned long long)entry.file_size();
			info.m_type = entry.is_directory() ? FileInfo::FileType::Folder : FileInfo::FileType::File;

			entries.emplace_back(info);
		}

		return entries;
	}

	DragonSystem* DragonSystem::Create()
	{
#if defined(_WIN32) || defined(_WIN64)
			return new WindowsSystem();
#else
		//"This operating system is not supported."
		return nullptr;
#endif
	}

};
