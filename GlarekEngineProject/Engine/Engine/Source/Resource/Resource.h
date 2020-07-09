#pragma once
/** \file Resource.h */
/** TODO: File Purpose */
// Created by Billy Graban


/** \class Resource */
/** TODO: Class Purpose */
#include <string>
#include <vector>

namespace Engine
{


	class Resource
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		Resource(const std::string& name, std::vector<char> data)
			: m_name(name)
			, m_data(move(data))
		{
		}

		const std::string& GetName() const { return m_name; }
		std::vector<char>& GetData() { return m_data; }

		/** Default Destructor */
		~Resource() {};


	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::string m_name;
		std::vector<char> m_data;


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}