#pragma once
/** \file WINSystem.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <sstream>
#include".\ISystem.h"
#include <vector>

#ifdef _SFML
#include "../Window/SFMLWindow.h"
#else
#include "../Window/SDLWindow.h"
#endif
namespace Engine
{
	/** \class WINSystem */
	/** TODO: Class Purpose */
	class WINSystem
		: public ISystem
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DLLEXP WINSystem() {};

		/** Default Destructor */
		DLLEXP ~WINSystem() {};

		//init system 
		bool Init() override;

		//log system info
		void LogSystemInfo() override;

		//open a message box
		void OpenMessageBox(const char* Name, const char* Message) override;

		//open an executable
		void OpenExe(const char* filepath, char **argv) override;

		//log directory contents under a filepath
		void LogDirectoryContents(std::string filepath) override;

		//get string: system timeStamp
		std::string GetSystemTimestamp() override;

		//get hard drive info
		void LogHardDriveInfo(const char* drive) override;

		//return user directory
		std::string GetUserDirectory() override;

		//void LogGpuInfo();

		std::vector<std::string> GetFilesInFolder(const char* path, bool recursive) override;

		void GetFiles(const char* path, std::vector<std::string>& vec, bool recursive);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//used to stream string
		std::stringstream m_stringstream;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get string: name of the system
		const char* GetSystemName() const override { return "WindowsSytem"; }
	};
}