#pragma once
/** \file ISystem.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>
#include <string>
#include <vector>

#include "../../Utility/Common.h"
#include "../Window/IWindow.h"

namespace Engine
{
	/** \class ISystem */
	/** TODO: Class Purpose */
	class ISystem
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DLLEXP ISystem() {};

		/** Default Destructor */
		DLLEXP virtual ~ISystem() {};

		//init system 
		DLLEXP virtual bool Init() = 0;

		//create a new system and return it
		DLLEXP static std::shared_ptr<ISystem> Create();

		//create a new system window and return it 
		DLLEXP std::unique_ptr<IWindow> CreateSystemWindow(const char* pTitle, u32 width, u32 height);

		//log system info
		DLLEXP virtual void LogSystemInfo() = 0;

		//open a message box
		DLLEXP virtual void OpenMessageBox(const char* Name, const char* Message) = 0;

		//open an executable
		DLLEXP virtual void OpenExe(const char* filepath, char **argv) = 0;

		//log directory contents under a filepath
		DLLEXP virtual void LogDirectoryContents(std::string filepath) = 0;

		//get string: system timeStamp
		DLLEXP virtual std::string GetSystemTimestamp() = 0;

		//get hard drive info
		DLLEXP virtual void LogHardDriveInfo(const char* drive) = 0;

		//return user directory
		DLLEXP virtual std::string GetUserDirectory() = 0;

		DLLEXP virtual std::vector<std::string> GetFilesInFolder(const char* path, bool recursive) = 0;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get name of the system
		virtual const char* GetSystemName() const = 0;

	};
}