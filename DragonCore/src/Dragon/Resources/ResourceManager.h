#pragma once

#include <Generic/StringHash.h>

#include <EASTL/queue.h>
#include <EASTL/unordered_map.h>
#include <EASTL/string.h>

#include <thread>

namespace dragon
{
	using ResourceId = uint64_t;

	/// <summary>
	/// TODO: Make thread safe.
	/// TODO: Create a "Helper" function to detect memory usage in the ResourceManager. E.g : GetMemoryUsage<Type>() and/or CalculateMemoryUsage
	/// TODO: Create a "Wrapper" around the ResourceMap to be able to "delete" the resource when the program exits.
	/// </summary>
	class ResourceManager
	{
		template<typename ResourceType>
		class ResourceMap
		{
			using Database = eastl::unordered_map<ResourceId, ResourceType*>;
			Database m_database;

		public:
			ResourceMap() = default;
			~ResourceMap()
			{
				for (auto pair : m_database)
				{
					delete pair.second;
				}
			}
		};

		using ResourceLoadJob = eastl::function<bool()>;
		using JobQueue = eastl::queue<ResourceLoadJob>;
		JobQueue m_loadJobs;

		JobQueue m_finishedJobs;

	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		auto& GetInstance()
		{
			static ResourceManager s_instance;
			return s_instance;
		}

		template<typename ResourceType, typename... Args>
		void LoadResource(const eastl::string& resourcePath, Args&&... args)
		{
			// Check if the resource is already loaded.
			if (FindResource(resourcePath) != nullptr)
				return;

			// TODO: Add a LoadResourceJob to the JobQueue
			// Signal the loader thread there are resources that can be loaded.
		}

		void Update()
		{
			// TODO: Finalize loaded resources.
			// Take hold of the "finalized" queue.
		}

	private:
		ResourceManager() = default;
		~ResourceManager()
		{
			// Clear the JobQueue

			// Signal the loader thread to exit and wait.
		}

		template<typename ResourceType>
		ResourceMap<ResourceType>& GetResourceDatabase()
		{
			static ResourceMap<ResourceType> s_resources;
			return s_resources;
		}

		template<typename ResourceType>
		ResourceType* FindResource(const eastl::string& resourcePath)
		{
			ResourceMap<ResourceType>& database = GetResourceDatabase<ResourceType>();

			ResourceId resourceId = hash_64_fnv1a_const(resourcePath.c_str());
			if (auto result = database.find(resourceId); result != database.end())
			{
				return (*result).second;
			}

			return nullptr;
		}
	};

}