#include "Debug.h"

#include <iostream>
#include <fstream>

namespace dragon
{
	Debug::Debug()
		: m_outputStreams()
	{
		Init();
	}

	void Debug::Init()
	{
		//m_outputStreams[0] = new ConsoleDebugStream();
		//m_outputStreams[1] = new FileDebugStream();
		//m_outputStreams[2] = new DebuggerDebugStream();
	}

	eastl::string Debug::VFormatMessage(const char* fmt, va_list args)
	{
		eastl::string msg;
		msg.sprintf_va_list(fmt, args);
		return msg;
	}

	void Debug::WriteEntry(const LogEntry& entry)
	{
		// entry.m_outputFlags.ForEach([this](DebugOutput output){
		//	auto outStream = m_outputStreams[output];
		//});

		assert(entry.m_pCategoryName != nullptr);

		//outStream.Lock();

		//outStream.SetColor(entry.m_color);
		//outStream << "[" << entry.m_pCategoryName << "]";

		// If the entry was made using a channel, Also write the channel.
		if (entry.m_pChannelName)
		{
			//outStream << "[" << entry.m_pChannelName << "]";
		}

		//outStream << entry.m_pFormattedMessage.c_str();

		//outStream.EndLine();

		//outStream.Unlock();
	}
}
