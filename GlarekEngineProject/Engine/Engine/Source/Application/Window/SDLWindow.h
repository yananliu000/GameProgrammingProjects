#pragma once
/** \file SDLWindow.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <memory>
#include <SDL2/SDL.h>

#include ".\IWindow.h"

namespace Engine
{
	/** \class SDLWindow */
	/** TODO: Class Purpose */
	class SDLWindow
		: public IWindow
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SDLWindow();

		/** Default Destructor */
		~SDLWindow();

		//init the window
		virtual bool Init(const char* pName, u32 width, u32 height) override;

		//converts a keycode from OS-land to our engine's definitions
		virtual IKeyboard::Code ConvertToCode(u32 key) override;

		//cnverts a button from OS-land to our engine's definitions
		virtual IMouse::Button ConvertToButton(u32 button) override;

		//poll and process events from the OS
		virtual bool ProcessEvents() override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//has the window been initialized?
		bool m_isInitialized;

		//unique_ptr of native window pointer: type name and destructor
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_pSFMLWindow;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the native window pointer
		virtual void* GetNativeWindow() const override;

	};
}