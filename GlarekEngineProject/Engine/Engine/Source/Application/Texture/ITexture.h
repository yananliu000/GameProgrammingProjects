#pragma once
/** \file ITexture.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "ITexture.h"
#include "../../Utility/Common.h"

namespace Engine
{
	/** \class ITexture */
	/** TODO: Class Purpose */
	class ITexture
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ITexture() {};

		/** Default Destructor */
		virtual ~ITexture() {};

		//get the pointer to the texture 
		virtual void* GetNativeTexture() = 0;

		//init from the filepath
		virtual bool Init(const char* filepath) = 0;

		

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


	};
}