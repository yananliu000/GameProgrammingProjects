#pragma once
/** \file ExitGameEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "IEvent.h"


/** \class ExitGameEvent */
/** TODO: Class Purpose */
namespace Engine
{
	class ExitGameEvent:public IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 4;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ExitGameEvent() {};

		/** Default Destructor */
		~ExitGameEvent() {};

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
		//get the event id
		u32 GetEventId() override { return m_kEventId; }

		//get the event name
		const char* GetName() override { return "ExitGameEvent"; }
	};
}