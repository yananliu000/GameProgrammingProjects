#include <iostream>
#include <Lua/lua.hpp>

#include "MyLogger.h"

using std::endl;

MyLogger::MyLogger()
{
	//main: argument the dash, valid option, anyone can specify the path, the default. 
	//predefine
	m_filepath = "GlarekSpecialLog.txt";
	m_safeLevel = LogLevel::Initial;
}

MyLogger::~MyLogger()
{
	m_outfile.close();
}

bool MyLogger::Init()
{
	m_outfile.open(m_configurtionPath + m_filepath);
	if (m_outfile.bad())
	{
		return false;
	}
	return true;
}

void MyLogger::write(LogLevel level, const std::string & msg)
{
	if (level > m_safeLevel)
	{
		if (m_pSystem != nullptr)
		{
			m_outfile << m_pSystem->GetSystemTimestamp();
		}
		m_outfile << "LogLevel:" << level << ", ";
		m_outfile << "Log Infomation: " << msg;
		m_outfile << endl;
	}
}

void MyLogger::PrintLoggingFile()
{
	std::ifstream f(m_configurtionPath + m_filepath);

	if (f.is_open())
	{
		std::cout << f.rdbuf();
	}
}

DLLEXP void MyLogger::SetConfigurationPath(char * path)
{
	m_configurtionPath = std::string(path);
}

int glua::Logger_Log(lua_State * pState)
{
	const char* message = lua_tostring(pState, -1);
	if (message != nullptr)
	{
		g_Logger.write(MyLogger::LogLevel::Game_Info, message);
	}
	return 0;
}

DLLEXP MyLogger g_Logger;
