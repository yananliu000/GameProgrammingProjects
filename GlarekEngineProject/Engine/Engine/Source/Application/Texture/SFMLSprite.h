#pragma once
/** \file SFMLSprite.h */
/** TODO: File Purpose */
// Created by Billy Graban
#ifdef _SFML
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include ".\ISprite.h"
namespace Engine
{
	/** \class SFMLSprite */
	/** TODO: Class Purpose */
	class SFMLSprite
		: public ISprite
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SFMLSprite() {};

		/** Default Destructor */
		~SFMLSprite() { delete m_pSprite; m_pSprite = nullptr; };

		//create sprite from texture
		bool Init(ITexture* pTexture) override;

		//create sprite from filepath
		bool Init(const char* filepath) override;

		void SetTint(Color tintColor) override { m_pSprite->setColor(sf::Color{ tintColor.red, tintColor.blue, tintColor.green });}

		void SetAlpha(u8 alpha) override { m_pSprite->setColor(sf::Color{ 255, 255, 255, alpha }); };

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the sprite
		sf::Sprite* m_pSprite;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the sprite pointer
		virtual void* GetNativeSprite() override { return m_pSprite; };

	};
}
#endif