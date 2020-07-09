#pragma once
/** \file ISprite.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "../../Utility/Common.h"

namespace Engine
{
	/** \class ISprite */
	/** TODO: Class Purpose */
	class ITexture;
	class ISprite
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ISprite() {};

		/** Default Destructor */
		virtual ~ISprite() {};

		//get the sprite pointer
		virtual void* GetNativeSprite() = 0;

		//init from texture to sprite
		virtual bool Init(ITexture* pTexture) = 0;

		//init from the filepath
		virtual bool Init(const char* filepath) = 0;

		virtual void SetTint(Color tintColor) = 0;

		virtual void SetAlpha(u8 alpha) = 0;

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