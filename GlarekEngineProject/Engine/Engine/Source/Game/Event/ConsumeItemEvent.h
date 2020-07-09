#pragma once
/** \file ConsumeItemEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <string>
#include "IEvent.h"

/** \class ConsumeItemEvent */
/** TODO: Class Purpose */
namespace Engine
{
	class Actor;
	//??? not sure how i represent item now
	class ConsumeItemEvent:public IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 2;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ConsumeItemEvent(Actor* pTarget, std::string Item):m_pPlayer(pTarget), m_item(Item) {};

		/** Default Destructor */
		~ConsumeItemEvent() {};

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
		const char* GetName() override { return "ConsumeItemEvent"; }

		Actor* GetPlayer() { return m_pPlayer; }

		std::string GetItem() { return m_item; }
	};
}