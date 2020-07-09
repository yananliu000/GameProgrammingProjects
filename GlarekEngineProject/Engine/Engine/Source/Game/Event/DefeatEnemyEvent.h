#pragma once
/** \file DefeatEnemyEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban


/** \class DefeatEnemyEvent */
/** TODO: Class Purpose */
#include "IEvent.h"

namespace Engine
{
	class Actor;
	class DefeatEnemyEvent:public IEvent
	{
		//enemy: die
		//player: get booty

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 3;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DefeatEnemyEvent(Actor* pPlayer, Actor* pEnemy) :m_pPlayer(pPlayer), m_pEnemy(pEnemy) {};

		/** Default Destructor */
		~DefeatEnemyEvent() {};

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		Actor* m_pPlayer;
		Actor* m_pEnemy;

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
		const char* GetName() override { return "DefeatEnemyEvent"; }

		Actor* GetPlayer() { return m_pPlayer; }
		Actor* GetEenemy() { return m_pEnemy; }
	};
}