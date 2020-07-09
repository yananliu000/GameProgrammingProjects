#pragma once
/** \file SDLSprite.h */
/** TODO: File Purpose */
// Created by Billy Graban

//ITexture => SDL_surface             SDLTexture class             
//ISprite => SDL_texture              SDLSprite class   (preferred)
//SDLSprite: actually SDL_Texture

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "ITexture.h"
#include "ISprite.h"
#include "../Graphic/SDLGraphic.h"

namespace Engine
{
	/** \class SDLSprite */
	/** TODO: Class Purpose */
	class SDLSprite
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
		DLLEXP SDLSprite() {}; //test DLLEXP

		/** Default Destructor */
		DLLEXP ~SDLSprite() { SDL_DestroyTexture(m_pSprite); m_pSprite = nullptr; }

		//create sprite from texture
		bool Init(ITexture* pTexture) override { m_pSprite = SDL_CreateTextureFromSurface(Engine::SDLGraphic::m_spRenderer, reinterpret_cast<SDL_Surface*>(pTexture->GetNativeTexture())); return (m_pSprite != nullptr); }

		//create sprite from filepath
		DLLEXP bool Init(const char* filepath) override {m_pSprite = IMG_LoadTexture(Engine::SDLGraphic::m_spRenderer, filepath); return (m_pSprite != nullptr);}

		void SetTint(Color tintColor) override { SDL_SetTextureColorMod(m_pSprite, tintColor.red, tintColor.green, tintColor.blue); }

		void SetAlpha(u8 alpha) override { SDL_SetTextureAlphaMod(m_pSprite, alpha); };

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the sprite
		SDL_Texture* m_pSprite;

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