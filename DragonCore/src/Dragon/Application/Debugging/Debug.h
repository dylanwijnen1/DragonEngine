#pragma once

#include <Dragon/Graphics/Color.h>

#include <Dragon/Generic/MacroMagic.h>

#include <EASTL/string_hash_map.h>

#include <mutex>
#include <iosfwd>

// TODO: Instead of enabling trace we should add trace functionality.
#if DRAGON_ENABLE_TRACE
	#define TRACE_FMT(fmt) __FILE__ "(" STRINGIFY(__LINE__) "): in function \"%s\":" fmt "\n\n"

	#define DDEBUG(CHANNEL, fmt, ...) dragon::Debug::GetInstance().WriteChannel(CHANNEL, TRACE_FMT(fmt), __FUNCTION__, __VA_ARGS__)
	#define DERR(fmt, ...) DDEBUG("Error", fmt, __VA_ARGS__)
	#define DWARN(fmt, ...) DDEBUG("Warning", fmt, __VA_ARGS__)
	#define DLOG(fmt, ...) DDEBUG("Info", fmt, __VA_ARGS__)
#else
	#define DDEBUG(CHANNEL, fmt, ...) dragon::Debug::GetInstance().WriteChannel(CHANNEL, fmt, __VA_ARGS__)
	#define DERR(fmt, ...) DDEBUG("Error", fmt, __VA_ARGS__)
	#define DWARN(fmt, ...) DDEBUG("Warning", fmt, __VA_ARGS__)
	#define DLOG(fmt, ...) DDEBUG("Info", fmt, __VA_ARGS__)
#endif

namespace dragon
{
	enum struct DebugOutput : uint8_t
	{
		None			= 0,
		File			= 1 << 0,		// File output
		Debugger		= 1 << 1,		// Debugger console (std::cout)
		Console			= 1 << 2,		// In Game Console
		All				= File | Debugger | Console,
	};
	ENUM_FLAG(DebugOutput)

	class Debug
	{
		struct Channel
		{
			Channel() = default;
			Channel(DebugOutput outputs, Color color)
				: m_outputs(outputs)
				, m_color(color)
				, m_enabled(true)
			{}

			DebugOutput m_outputs;
			Color m_color;
			bool m_enabled;
		};

		using ChannelMap = eastl::string_hash_map<Channel>;
		ChannelMap m_channelMap;

		std::mutex m_debugLock;
		std::ostream* m_pDebugger;
		std::mutex m_fileLock;
		std::ofstream* m_pFile;
		std::mutex m_consoleLock;
		std::ostream* m_pConsole;

		class DragonSystem* m_pSystem;

	public:
		static auto& GetInstance()
		{
			static Debug instance;
			return instance;
		}

		~Debug();

		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator=(const Debug&) = delete;
		Debug& operator=(Debug&&) = delete;

		// Create the 3 default channels, Error, Warning, Info
		bool Init();

		template<typename... Args>
		void EmplaceChannel(Args&&... args);

		void CreateChannel(const char* name, Color color = Colors::White);
		void CreateChannel(const char* name, DebugOutput outputs, Color color = Colors::White);

		void DisableChannel(const char* name);
		void EnableChannel(const char* name);

		void WriteChannel(const char* channel, const char* fmt, ...);

		void SetSystem(DragonSystem* pSystem) { m_pSystem = pSystem; }
	
	private:
		Debug()
			: m_pConsole(nullptr)
			, m_pDebugger(nullptr)
			, m_pFile(nullptr)
			, m_pSystem(nullptr)
		{}
	};

	template<typename ...Args>
	inline void Debug::EmplaceChannel(Args&& ...args)
	{
		m_channelMap.emplace(std::forward(args));
	}
}