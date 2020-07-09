#pragma once
/** \file ContactListener.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <Box2D/Box2D.h>
#include <vector>

/** \class ContactListener */
/** TODO: Class Purpose */
namespace Engine
{
	class Actor;
	class IPhysics;

	class ContactListener : public b2ContactListener
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ContactListener(IPhysics* pPhysics) : m_pPhysicsSystem(pPhysics) {};

		/** Default Destructor */
		~ContactListener() = default;

		//handles the start of contact between two fixtures
		virtual void BeginContact(b2Contact* pContact) override;

		//handles the end of contact between two fixtures
		virtual void EndContact(b2Contact* pContact) override;

		//clear all collisions 
		void ClearContacts() { m_collisions.clear(); }

		//handle all collisions on the list
		void HandleCollisions();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		struct CollisionData
		{
			Actor* m_pActor;	 //the actor	
			Actor* m_pOther;	//the other actor	
			bool m_isContact; //state of the collision: true =>still contact & false => not contact anymore
		};

		//the physics world
		IPhysics* m_pPhysicsSystem;

		//list of collisions this frame
		std::vector<CollisionData> m_collisions;
		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}