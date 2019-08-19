#include "Debug.h"

#include <Dragon/Config.h>
#include <Dragon/Application/System/DragonSystem.h>

#include <iostream>
#include <fstream>

#include <variant>


namespace dragon
{
	static constexpr DebugOutput kStandardOutputs = DebugOutput::Debugger | DebugOutput::File;
	static constexpr Color kDefaultColor = Colors::White;

	Debug::~Debug()
	{
		m_pFile->close();
		delete m_pFile;
	}

	bool Debug::Init()
	{
		m_channelMap.try_emplace("Error", Channel { kStandardOutputs, Colors::Red });
		m_channelMap.try_emplace("Warning", Channel { kStandardOutputs, Colors::Yellow });
		m_channelMap.try_emplace("Info", Channel { kStandardOutputs, Colors::Green });

		m_pDebugger = &std::cout;
		//m_pFile = new std::ofstream(, ) // Create a new file with the current timestamp.

		return true;
	}

	void Debug::CreateChannel(const char* name, Color color)
	{
		m_channelMap.try_emplace(name, Channel { DebugOutput::All, color });
	}

	void Debug::CreateChannel(const char* name, DebugOutput outputs, Color color)
	{
		m_channelMap.try_emplace(name, Channel { outputs, color });
	}

	void Debug::DisableChannel(const char* name)
	{
		if (auto result = m_channelMap.find(name); result != m_channelMap.end())
		{
			(*result).second.m_enabled = false;
		}
	}

	void Debug::EnableChannel(const char* name)
	{
		if (auto result = m_channelMap.find(name); result != m_channelMap.end())
		{
			(*result).second.m_enabled = true;
		}
	}

	void Debug::WriteChannel(const char* channel, const char* fmt, ...)
	{
		Channel ch;

		if (auto result = m_channelMap.find(channel); result == m_channelMap.end())
		{
			ch = (*result).second;
		}
		else
		{
			ch = m_channelMap.try_emplace(channel, Channel { DebugOutput::All, kDefaultColor }).first->second;
		}

		eastl::string outputText = "";

		va_list args;
		va_start(args, fmt);
		outputText.sprintf_va_list(fmt, args);
		va_end(args);

		if (ch.m_outputs & DebugOutput::Debugger)
		{
			m_debugLock.lock();

			if(m_pSystem)
				m_pSystem->SetConsoleColor(ch.m_color);
			
			if(m_pDebugger)
				*m_pDebugger << "[" << channel << "] " << outputText.c_str() << std::endl;

			m_debugLock.unlock();
		}

		if (ch.m_outputs & DebugOutput::File)
		{
			m_fileLock.lock();
			*m_pFile << "[" << channel << "] " << outputText.c_str() << std::endl;
			m_fileLock.unlock();
		}

		if (ch.m_outputs & DebugOutput::Console)
		{
			m_consoleLock.lock();
			*m_pConsole << "[" << channel << "] " << outputText.c_str() << std::endl;
			m_consoleLock.unlock();
		}

	}
}
