#pragma once
/** \file IKeyboard.h */
/** TODO: File Purpose */
// Created by Billy Graban


/** \class IKeyboard */
/** TODO: Class Purpose */

#include <memory>

#include "../../Utility/Common.h"
namespace Engine
{
	class IKeyboard
	{
	public:
		enum State
		{
			kUp,
			kDown,
			kRelease,
			kPress
		};

		enum Code
		{
			kCodeA,
			kCodeB,
			kCodeC,
			kCodeD,
			kCodeE,
			kCodeF,
			kCodeG,
			kCodeH,
			kCodeI,
			kCodeJ,
			kCodeK,
			kCodeL,
			kCodeM,
			kCodeN,
			kCodeO,
			kCodeP,
			kCodeQ,
			kCodeR,
			kCodeS,
			kCodeT,
			kCodeU,
			kCodeV,
			kCodeW,
			kCodeX,
			kCodeY,
			kCodeZ,

			kCode0,
			kCode1,
			kCode2,
			kCode3,
			kCode4,
			kCode5,
			kCode6,
			kCode7,
			kCode8,
			kCode9,

			kCodeEscape,
			kCodeEnter,
			kCodeRightArrow,
			kCodeUpArrow,
			kCodeLeftArrow,
			kCodeDownArrow,
			kCodeSpacebar,

			kCodeMax
		};

		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IKeyboard() {};

		/** Default Destructor */
		virtual ~IKeyboard() {};

		//init the keyboard input system
		bool Init();

		//set the state of a key
		DLLEXP void SetKeyState(Code code, bool isDown);

		//is key just pressed
		DLLEXP bool IsKeyPressed(Code code);

		//is key down
		DLLEXP bool IsKeyDown(Code code);

		//update states of keys who are just pressed or released to down and up
		void NextFrame();

		//create a new keyboard input system and return it
		static std::unique_ptr<IKeyboard> Create() { return std::unique_ptr<IKeyboard>(new IKeyboard()); }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//an array of key states with kCodeMax size
		State m_buttonState[kCodeMax];

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
	};
}