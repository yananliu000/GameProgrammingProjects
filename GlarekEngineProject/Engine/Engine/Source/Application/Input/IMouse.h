#pragma once
/** \file IMouse.h */
/** TODO: File Purpose */
// Created by Billy Graban


/** \class IMouse */
/** TODO: Class Purpose */

#include <memory>
#include <array>

#include "../../Math/Vector2.h"
#include "../../Utility/Common.h"

namespace Engine
{
	class IGraphic;
	class IMouse
	{
	public:

		enum Button
		{
			kButtonLeft,
			kButtonRight,
			kButtonMiddle,

			kButtonNum
		};

		enum State
		{
			kUp,
			kDown,
			kRelease,
			kPress
		};
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IMouse() 
			: m_position{ 0,0 }
			, m_buttonState{ kRelease }	
			, m_graphicReference(nullptr)
			{}

		/** Default Destructor */
		~IMouse() {}

		//init the mouse input system
		bool Init(Engine::IGraphic* graphicReference);

		//set the state of a button
		void SetButtonState(Button button, bool isDown);

		//is button just pressed
		bool IsButtonPressed(Button button);

		//is button down
		bool IsButtonDown(Button button);

		//update states of buttons who are just pressed or released to down and up
		void NextFrame();

		//create a new mouse input system and return it
		static std::unique_ptr<IMouse> Create() { return std::unique_ptr<IMouse>(new IMouse()); }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		// position of the mouse on screen
		V2f m_position;
		std::array<State, kButtonNum> m_buttonState;
		IGraphic* m_graphicReference;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		V2f GetMousePosition();
	};
}