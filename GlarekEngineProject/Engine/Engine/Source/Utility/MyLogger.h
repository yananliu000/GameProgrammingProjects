#pragma once
/** \file MyLogger.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <string>
#include <memory>
#include <fstream> //output 

#include "../Application/System/ISystem.h"
#include "Common.h"
/** \class MyLogger */
/** TODO: Class Purpose */

struct lua_State;
namespace glua
{
	//class.gen.h
	//class.gen.cpp
	__declspec(dllexport) int Logger_Log(lua_State* pState);
}

class Engine::ISystem;
class MyLogger
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //
	enum LogLevel
	{
		Initial,
		System_Normal,
		System_Error,
		System_Warning,
		Game_Info,
		Game_Error,
		Game_Warning
	};

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	DLLEXP MyLogger();

	/** Default Destructor */
	DLLEXP ~MyLogger();

	//Initialization of the logger
	bool Init();

	//input the string to output it into the file
	void write(LogLevel level, const std::string& msg);

	//print the logging file
	void PrintLoggingFile();

	
private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	std::string m_filepath;
	std::string m_configurtionPath;
	std::ofstream m_outfile;
	LogLevel m_safeLevel;
	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	std::shared_ptr<Engine::ISystem> m_pSystem;

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	//set the safe level
	void SetSafeLevel(LogLevel level) { m_safeLevel = level; }

	//set the system pointer
	void SetSystem(std::shared_ptr<Engine::ISystem> pSystem) { m_pSystem = pSystem; };

	//set configuration path
	DLLEXP void SetConfigurationPath(char* path);
};

DLLEXP extern MyLogger g_Logger;

