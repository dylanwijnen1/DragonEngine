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
		if (m_pFile)
		{
			m_pFile->close();
			delete m_pFile;
		}
	}

	bool Debug::Init()
	{
		// TODO: Can't use emplace_back because it doesn't handle passing in a literal string. Waiting for EASTL to fix this bug. https://github.com/electronicarts/EASTL/issues/269
		m_channelMap.insert_or_assign("Error", Channel { kStandardOutputs/*, Colors::Red*/ });
		m_channelMap.insert_or_assign("Warning", Channel { kStandardOutputs/*, Colors::Yellow*/ });
		m_channelMap.insert_or_assign("Info", Channel { kStandardOutputs/*, Colors::Green*/ });

		m_pDebugger = &std::cout;
		//m_pFile = new std::ofstream(, ) // Create a new file with the current timestamp.

		return true;
	}

	/*void Debug::CreateChannel(const char* name, Color color)
	{
		m_channelMap.try_emplace(name, Channel { DebugOutput::All, color });
	}

	void Debug::CreateChannel(const char* name, DebugOutput outputs, Color color)
	{
		m_channelMap.try_emplace(name, Channel { outputs, color });
	}*/

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
			ch = m_channelMap.try_emplace(channel, Channel { DebugOutput::All/*, kDefaultColor*/ }).first->second;
		}

		eastl::string outputText = "";

		va_list args;
		va_start(args, fmt);
		outputText.sprintf_va_list(fmt, args);
		va_end(args);

		if (ch.m_outputs & DebugOutput::Debugger && m_pDebugger)
		{
			m_debugLock.lock();

			/*if(m_pSystem)
				m_pSystem->SetConsoleColor(ch.m_color);*/
			
			if(m_pDebugger)
				*m_pDebugger << "[" << channel << "] " << outputText.c_str() << std::endl;

			m_debugLock.unlock();
		}

		if (ch.m_outputs & DebugOutput::File && m_pFile)
		{		
			m_fileLock.lock();
			*m_pFile << "[" << channel << "] " << outputText.c_str() << std::endl;
			m_fileLock.unlock();
		}

		if (ch.m_outputs & DebugOutput::Console && m_pConsole)
		{
			m_consoleLock.lock();
			*m_pConsole << "[" << channel << "] " << outputText.c_str() << std::endl;
			m_consoleLock.unlock();
		}

	}
}
