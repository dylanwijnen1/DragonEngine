#pragma once

#include <Dragon/Config.h>

#include <Dragon/Graphics/Color.h>
#include <Dragon/Generic/MacroMagic.h>

#include <EASTL/string.h>
#include <EASTL/array.h>

#include <cstdarg>
#include <mutex>
#include <iosfwd>

namespace dragon
{
	enum struct DebugOutput : uint8_t
	{
		None = 0,
		File = 1 << 0,		// File output
		Debugger = 1 << 1,		// Debugger console (std::cout)
		Console = 1 << 2,		// In Game Console
		All = File | Debugger | Console,
		kSize = 3
	};
	ENUM_FLAG(DebugOutput);

	class DebugStream
	{
	protected:
		std::mutex m_streamLock;
	public:
		void Lock()
		{
			m_streamLock.lock();
		}

		void Unlock()
		{
#pragma warning(push)
#pragma warning(disable : 26110)
			// Ignoring the warning about locking and unlocking not within the same context.
			m_streamLock.unlock();
#pragma warning(pop)
		}

		virtual void SetColor(dragon::Color color) = 0;
		virtual void EndLine() = 0;
		virtual void operator<<(const char* text) = 0;
	};

	class Debug
	{
	private:

		/// <summary>
		/// A struct that contains data about a message that needs to be logged.
		/// </summary>
		struct LogEntry
		{
			const char* m_pChannelName;
			const char* m_pCategoryName;
			eastl::string m_pFormattedMessage; // Contains only the formatted message.
			Color m_color;
			DebugOutput m_outputFlags;
			// TimeStamp?
		};

		eastl::array<DebugStream*, (size_t)DebugOutput::kSize> m_outputStreams;

	public:
		/// <summary>
		/// Channels are solely to disable/enable output for a specific module.
		/// Example :
		/// <code>
		/// </code>
		/// </summary>
		template<typename Type>
		struct Channel
		{
			inline static constexpr const char* kName = nullptr;
			bool m_enabled;

			Channel()
				: m_enabled(true)
			{
				// Register Channel with Debug Scripting Instance. Debug::RegisterChannel(this);
			}

			static Channel<Type>& GetInstance()
			{
				static Channel<Type> s_channel;
				return s_channel;
			}
		};

		/// <summary>
		/// Error, Warning, Log, Info, Game
		/// Defining a new category can be done like :
		/// <code>
		///		DDEBUG_NEW_CATEGORY(Foo)
		///		DDEBUG_NEW_CATEGORY(Foo, Colors::Purple, DebugOutput::File | DebugOutput::Console)
		/// </code>
		/// </summary>
		template<typename Type>
		struct Category
		{
			bool m_enabled;
			DebugOutput m_outputFlags;

			Category()
				: m_enabled(true)
				, m_outputFlags(DebugOutput::All)
			{}

			Category(Color color, DebugOutput outputFlags)
				: m_enabled(true)
			{}

			static Category<Type>& GetInstance()
			{
				static Category<Type> s_cat;
				return s_cat;
			}
		};

		/// <summary>
		/// Standard logging function, Uses default log settings.
		/// </summary>
		/// <param name="fmt"></param>
		/// <param name=""></param>
		static void Log(const char* fmt, ...);

		template<typename Cat>
		static void Log(const char* fmt, ...)
		{
			auto category = Category<Cat>::GetInstance();
			if (!category.m_enabled)
				return; // Exit early if category is disabled.
			
			// Create a new log entry struct.
			LogEntry entry;
			entry.m_pCategoryName = Cat::kName;
			entry.m_color = Cat::kColor;

			// Format the message
			va_list vargs;
			va_start(vargs, fmt);
			entry.m_pFormattedMessage = VFormatMessage(fmt, vargs);
			va_end(vargs);

			auto self = GetInstance();
			self.WriteEntry(entry);
		}

	private:

		Debug();

		void Init();

		static Debug& GetInstance()
		{
			static Debug s_debug;
			return s_debug;
		}

		static eastl::string VFormatMessage(const char* fmt, va_list args);

		/// <summary>
		/// Writes the entry to the respective outputs
		/// </summary>
		/// <param name="entry"></param>
		void WriteEntry(const LogEntry& entry);

	};
};

#define DDEBUG_NEW_CATEGORY(CATEGORY) DDEBUG_NEW_CATEGORY_ADVANCED(CATEGORY, Colors::White, DebugOutput::All)

#define DDEBUG_NEW_CATEGORY_ADVANCED(CATEGORY, COLOR, OUTPUTFLAGS)															\
namespace dragon																											\
{																															\
	namespace _debug																										\
	{																														\
		struct CATEGORY																										\
		{																													\
			inline static constexpr const char* kName = #CATEGORY;															\
			inline static constexpr Color kColor = COLOR;																	\
			inline static constexpr DebugOutput kDefaultOutputs = OUTPUTFLAGS;												\
		};																													\
		static Debug::Category<CATEGORY>& g_instance##CATEGORY = Debug::Category<CATEGORY>::GetInstance();					\
	}																														\
}																															\

DDEBUG_NEW_CATEGORY_ADVANCED(Error, Colors::Red, DebugOutput::All);
DDEBUG_NEW_CATEGORY_ADVANCED(Warning, Colors::Yellow, DebugOutput::All);
DDEBUG_NEW_CATEGORY_ADVANCED(Info, Colors::Green, DebugOutput::All);

// Debug Helpers
#define DDEBUG_INTERNAL(CATEGORY, fmt, ...) dragon::Debug::Log<dragon::_debug::##CATEGORY>(fmt, __VA_ARGS__)

#define DLOG(fmt, ...) dragon::Debug::Log(fmt, __VA_ARGS__);
#define DDEBUG(CATEGORY, CHANNEL, fmt, ...) dragon::Debug::Log<dragon::_debug::##CATEGORY, dragon::_debug::##CHANNEL>(fmt, __VA_ARGS__)
#define DERR(fmt, ...) DDEBUG_INTERNAL(Error, fmt, __VA_ARGS__)
#define DWARN(fmt, ...) DDEBUG_INTERNAL(Warning, fmt, __VA_ARGS__)
#define DINFO(fmt, ...) DDEBUG_INTERNAL(Info, fmt, __VA_ARGS__)

// Trace Helpers
#define TRACE_FMT(fmt) __FILE__ "(" STRINGIFY(__LINE__) "): in function \"%s\":" fmt "\n\n"
#define DDEBUG_TRACE_INTERNAL(CATEGORY, fmt, ...) DDEBUG_INTERNAL(CATEGORY, TRACE_FMT(fmt), __FUNCTION__, __VA_ARGS__)

#define DLOG_TRACE(fmt, ...) DLOG(TRACE_FMT(fmt), __VA_ARGS__)
#define DDEBUG_TRACE(CATEGORY, CHANNEL, fmt, ...) DDEBUG(CATEGORY, CHANNEL, TRACE_FMT(fmt), __FUNCTION__, __VA_ARGS__)
#define DERR_TRACE(fmt, ...) DDEBUG_TRACE_INTERNAL(Error, fmt, __VA_ARGS__)
#define DWARN_TRACE(fmt, ...) DDEBUG_TRACE_INTERNAL(Warning, fmt, __VA_ARGS__)
#define DINFO_TRACE(fmt, ...) DDEBUG_TRACE_INTERNAL(Info, fmt, __VA_ARGS__)