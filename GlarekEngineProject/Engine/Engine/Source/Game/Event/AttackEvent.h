#pragma once
/** \file AttackEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include ".\IEvent.h"

/** \class AttackEvent */
/** TODO: Class Purpose */
namespace Engine
{
	//attacker: attack
	//target: get hurt, check if die, true => defeat enemy event

	class Actor;
	class AttackEvent
		: public IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 1;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		AttackEvent(Actor* pAttacker, Actor* pTarget):m_pAttacker(pAttacker), m_pTarget(pTarget){};

		/** Default Destructor */
		~AttackEvent() {};

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		Actor* m_pAttacker;
		Actor* m_pTarget;

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
		const char* GetName() override { return "AttackEvent"; }

		Actor* GetAttacker() { return m_pAttacker; }
		Actor* GEtTarget() { return m_pTarget; }
	};
}

