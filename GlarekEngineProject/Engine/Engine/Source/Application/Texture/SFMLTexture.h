#pragma once
/** \file SFMLTexture.h */
/** TODO: File Purpose */
// Created by Billy Graban
//#ifdef _SFML
#ifdef _SFML


#include <SFML/Graphics/Texture.hpp>

#include ".\ITexture.h"

namespace Engine
{
	/** \class SFMLTexture */
	/** TODO: Class Purpose */
	class SFMLTexture
		: public ITexture
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SFMLTexture() {};

		/** Default Destructor */
		~SFMLTexture() { delete m_ptexture; m_ptexture = nullptr; };

		//create sprite from filepath ???
		bool Init(const char* filepath) override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the texture pointer
		sf::Texture* m_ptexture;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the sprite pointer
		virtual void* GetNativeTexture() override { return m_ptexture; }

	};
}
#endif // _SFML
