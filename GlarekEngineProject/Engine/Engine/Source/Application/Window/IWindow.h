#pragma once
/** \file IWindow.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <memory>

#include "../../Utility/Common.h"
#include "../../Application/Input/IKeyboard.h"
#include "../../Application/Input/IMouse.h"

namespace Engine
{
	/** \class IWindow */
	/** TODO: Class Purpose */
	class IWindow
	{
	protected:
		// --------------------------------------------------------------------- //
		// protected Member Variables
		// --------------------------------------------------------------------- //
		//owns the keyboard pointer
		std::unique_ptr<IKeyboard> m_pKeyboard;

		//owns the mouse pointer
		std::unique_ptr<IMouse> m_pMouse;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IWindow() {};

		/** Default Destructor */
		virtual ~IWindow() {};

		//init a window
		virtual bool Init(const char* pName, u32 width, u32 height) = 0;

		//advance the keyboard and mouse interfaces to prepare for the next frame
		virtual void NextFrame() { if (m_pMouse) { m_pMouse->NextFrame(); } if (m_pKeyboard) { m_pKeyboard->NextFrame(); } };

		//converts a keycode from OS-land to our engine's definitions
		virtual IKeyboard::Code ConvertToCode(u32 key) = 0;

		//converts a button from OS-land to our engine's definitions
		virtual IMouse::Button ConvertToButton(u32 button) = 0;

		//poll and process events from the OS
		virtual bool ProcessEvents() = 0;

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
		//get the native window
		virtual void* GetNativeWindow() const = 0;

		//atach a keyboard interface to the window
		virtual void SetKeyboard(std::unique_ptr<IKeyboard> pKeyboard) { m_pKeyboard = std::move(pKeyboard); }

		//get a raw pointer to the keyboard
		IKeyboard* GetKeyboard() { return m_pKeyboard.get(); }

		//attach a mouse interface to the window
		virtual void SetMouse(std::unique_ptr<IMouse> pMouse) { m_pMouse = std::move(pMouse); }

		//get a raw pointer to the mouse
		IMouse* GetMouse() { return m_pMouse.get(); }

	};
}