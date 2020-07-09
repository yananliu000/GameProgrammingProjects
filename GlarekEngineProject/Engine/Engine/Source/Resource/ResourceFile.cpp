#include <algorithm> //transform
#include <string> //replace
#include <Zlib/zlib.h>
#include <Tinyxml2/tinyxml2.h>
#include <memory>

#include "Resource.h"
#include "ResourceFile.h"

using Engine::ResourceFile;

void Engine::ResourceFile::AddResource(std::string path, std::vector<char> data)
{
	/*
	//normalize path 
	std::transform(path.begin(), path.end(), path.begin(), ::tolower);
	replace(path.begin(), path.end(), '\\', '/');

	//record keeping
	ResourceInfo info;
	info.m_size = static_cast<u32>(data.size());
	info.m_offset = m_currentOffset;

	std::vector<char> compressedData;
	compressedData.resize(data.size());

	//initializing zlib stream: input out data into zlib deflate function
	//static_cast & reinterpret_cast: zlib formats 
	z_stream stream;
	memset(&stream, 0, sizeof(stream));
	stream.avail_in = static_cast<u32>(data.size());
	stream.next_in = reinterpret_cast<u8*>(data.data());
	stream.avail_out = static_cast<u32>(compressedData.size());
	stream.next_out = reinterpret_cast<u8*>(compressedData.data());
	int result = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
	if (result != Z_OK)
	{
		//should log something here: bail
		return;
	}

	result = deflate(&stream, Z_FINISH);
	if (result == Z_STREAM_END && stream.total_out < data.size() && stream.avail_in == 0)
	{
		compressedData.resize(stream.total_out);
	}
	else
	{
		//if compressed size is bigger than the original size, use uncompressed
		compressedData = move(data);
	}
	//tell zlib free the allocated memory
	deflateEnd(&stream);

	//save everything
	info.m_compressed = static_cast<u32>(compressedData.size());
	m_currentOffset += info.m_compressed;
	m_infoMap[path] = info;
	m_pendingData.push_back(move(compressedData));
	*/
}

//structure of the resource file
//data
//infos => header
//header size (the reserved special bit)
void Engine::ResourceFile::Save(const std::string & path)
{
	//set up xml file. add root element
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* pRoot = doc.NewElement("ResourceFile");
	doc.InsertFirstChild(pRoot);

	//for each info, create an element
	for (auto& info : m_infoMap)
	{
		tinyxml2::XMLElement* pElement = doc.NewElement("Resource");
		pElement->SetAttribute("Path", info.first.c_str());
		pElement->SetAttribute("Compressed", info.second.m_compressed);
		pElement->SetAttribute("Size", info.second.m_size);
		pElement->SetAttribute("Offset", info.second.m_offset);
		pRoot->InsertEndChild(pElement);
	}

	//turn the xml document into a string, so we can write string to disk
	tinyxml2::XMLPrinter print;
	doc.Print(&print);

	//write everything to disk
	m_file.open(path, std::ios_base::out | std::ios_base::binary);
	if (m_file.is_open())
	{
		for (auto& data : m_pendingData)
		{
			m_file.write(data.data(), data.size());
		}
		m_file.write(print.CStr(), print.CStrSize());

		//write out the size of our header
		//int: means the size of header cannot be more than 4GB
		//double check here (mark)
		int size = print.CStrSize();
		m_file.write(reinterpret_cast<char*>(&size), sizeof(int));

		m_pendingData.clear();
		m_infoMap.clear();
		m_currentOffset = 0;
	}
	m_file.close();
}

std::shared_ptr<Engine::Resource> Engine::ResourceFile::LoadResource(std::string path)
{
	/*
	if (!m_file.is_open())
	{
		return nullptr;
	}

	transform(path.begin(), path.end(), path.begin(), ::tolower);
	replace(path.begin(), path.end(), '\\', '/');

	auto itr = m_infoMap.find(path);
	if (itr == m_infoMap.end())
	{
		return nullptr;
	}

	std::vector<char> compressed(itr->second.m_compressed);
	m_file.seekg(itr->second.m_offset);
	m_file.read(compressed.data(), compressed.size());

	if (itr->second.m_size == itr->second.m_compressed)
	{
		return std::make_shared<Engine::Resource>(path, move(compressed));
	}

	std::vector<char> data(itr->second.m_size);

	z_stream stream;
	memset(&stream, 0, sizeof(stream));
	stream.avail_in = static_cast<uint32_t>(compressed.size());
	stream.next_in = reinterpret_cast<uint8_t*>(compressed.data());
	stream.avail_out = static_cast<uint32_t>(data.size());
	stream.next_out = reinterpret_cast<uint8_t*>(data.data());
	int result = inflateInit(&stream);
	if (result != Z_OK)
	{
		return nullptr;
	}

	result = inflate(&stream, Z_FINISH);
	if (result != Z_STREAM_END)
	{
		return nullptr;
	}

	return std::make_shared<Engine::Resource>(path, move(data));
	*/
	return nullptr;
}

void Engine::ResourceFile::Load(const std::string & path)
{
	m_file.open(path, std::ios_base::in | std::ios_base::binary);
	if (m_file.is_open())
	{
		int sizeofInt = sizeof(int);
		m_file.seekg(-sizeofInt, m_file.end);
		int headerSize;
		m_file.read(reinterpret_cast<char*>(&headerSize), sizeof(int));
		m_file.seekg(-(headerSize + sizeofInt), m_file.cur);

		std::vector<char> header(headerSize);
		m_file.read(header.data(), headerSize);

		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError error = doc.Parse(header.data(), headerSize);
		if (error != tinyxml2::XML_SUCCESS)
		{
			return;
		}

		tinyxml2::XMLElement* pRoot = doc.FirstChildElement();
		std::string name(pRoot->Name());
		if (name == "ResourceFile")
		{
			for (tinyxml2::XMLElement* pElement = pRoot->FirstChildElement(); pElement;
				pElement = pElement->NextSiblingElement())
			{
				std::string elementName(pElement->Name());
				if (elementName == "Resource")
				{
					ResourceInfo info;
					info.m_compressed = pElement->UnsignedAttribute("Compressed");
					info.m_size = pElement->UnsignedAttribute("Size");
					info.m_offset = pElement->UnsignedAttribute("Offset");
					std::string path = pElement->Attribute("Path");
					if (!path.empty())
					{
						m_infoMap[path] = info;
					}
				}
			}
		}
	}
}
