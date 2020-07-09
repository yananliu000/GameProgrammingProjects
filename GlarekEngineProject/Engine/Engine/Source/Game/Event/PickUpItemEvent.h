#pragma once
/** \file PickUpItemEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "IEvent.h"
#include <string>

/** \class PickUpItemEvent */
/** TODO: Class Purpose */
namespace Engine
{
	class Actor;
	class PickUpItemEvent:public IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 5;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		PickUpItemEvent(Actor* pTarget, std::string Item): m_pPlayer(pTarget), m_item(Item) {};

		/** Default Destructor */
		~PickUpItemEvent() {};

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		Actor* m_pPlayer;
		std::string m_item;

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
		const char* GetName() override { return "PickUpItemEvent"; }

		Actor* GetPlayer() { return m_pPlayer; }

		std::string GetItem() { return m_item; }
	};
}