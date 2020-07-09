#pragma once
//sound: pause stop play

/** \file IEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include "../../Utility/Common.h"

/** \class IEvent */
/** TODO: Class Purpose */
namespace Engine
{
	class IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//identifier for events
		u32 EventId;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IEvent() {};

		/** Default Destructor */
		~IEvent() {};

		//return the event identifier
		virtual u32 GetEventId() = 0;

		//return a human-readable name of the event for logging
		virtual const char* GetName() = 0;

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