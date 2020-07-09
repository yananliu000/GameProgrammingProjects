#pragma once
/** \file SDLTexture.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ITexture.h"

namespace Engine
{
	/** \class SDLTexture */
	/** TODO: Class Purpose */
	class SDLTexture
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
		SDLTexture() {};

		/** Default Destructor */
		~SDLTexture() { SDL_FreeSurface(m_pSurface); m_pSurface = nullptr; };

		//load sdl_surface from the filepath: use IMG_Load here
		bool Init(const char* filepath) override { m_pSurface = IMG_Load(filepath); return m_pSurface; };


	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the texture pointer
		SDL_Surface* m_pSurface;


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//return sdl_surface
		virtual void* GetNativeTexture() override { return m_pSurface; };

	};
}