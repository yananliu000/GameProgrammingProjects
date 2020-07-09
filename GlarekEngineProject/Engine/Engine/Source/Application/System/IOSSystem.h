#pragma once
/** \file IOSSystem.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include".\ISystem.h"
namespace Engine
{
	/** \class IOSSystem */
	/** TODO: Class Purpose */
	class IOSSystem
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
		DLLEXP IOSSystem();

		/** Default Destructor */
		DLLEXP ~IOSSystem();

		//init system 
		bool Init() override;

		//log system info
		void LogSystemInfo() override {};

		//open a message box
		void OpenMessageBox(const char* Name, const char* Message) override {};

		//open an executable
		void OpenExe(const char* filepath, char **argv) {};

		//log directory contents under a filepath
		void LogDirectoryContents(std::string filepath) override {};

		//get string: system timeStamp
		std::string GetSystemTimestamp() override { return "Unfinished"; };

		//get hard drive info
		void LogHardDriveInfo(const char* drive) override {};

		//return user directory
		std::string GetUserDirectory() override { return "Unfinished"; };

		std::vector<std::string> GetFilesInFolder(const char* path, bool recursive) override { std::vector<std::string> v; return v; };

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
		//get string: name of the system
		const char* GetSystemName() const override { return "AppleSytem"; }

	};
}