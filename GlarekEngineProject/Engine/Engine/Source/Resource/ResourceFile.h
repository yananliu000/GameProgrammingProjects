#pragma once
#include <unordered_map>
#include <fstream>
#include "../Utility/Common.h"

/** \file ResourceFile.h */
/** TODO: File Purpose */
// Created by Billy Graban


/** \class ResourceFile */
/** TODO: Class Purpose */
namespace Engine
{
	class Resource;
	class ResourceFile
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ResourceFile()
			: m_currentOffset(0)
		{
		}

		/** Default Destructor */
		~ResourceFile() {};

		//
		DLLEXP void AddResource(std::string path, std::vector<char> data);

		//
		void Save(const std::string& path);

		DLLEXP std::shared_ptr<Resource> LoadResource(std::string path);

		void Load(const std::string& path);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //

		//keep track of the basic information about resources
		struct ResourceInfo
		{
			u32 m_compressed; //the compressed size 
			u32 m_size; //the uncompressed size 
			u32 m_offset; //the offset in the file 
		};

		std::unordered_map<std::string, ResourceInfo> m_infoMap;

		//where in our file the next resource will be located at
		u32 m_currentOffset;

		//contain the pending data of all the resources that is waiting to be written to disk
		//use a vector of vectors: pass memory, not copying stuff 
		std::vector<std::vector<char>> m_pendingData;

		//file handle: access disk file
		std::fstream m_file;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}