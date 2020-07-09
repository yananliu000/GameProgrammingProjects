#pragma once
/** \file IPhysics.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <Box2D/Box2D.h>

#include "../../Utility/Common.h"
#include "ContactListener.h"
#include "PhysicsVisualDebug.h"

/** \class IPhysics */
/** TODO: Class Purpose */
namespace Engine
{
	class IPhysics
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IPhysics() :m_world(b2Vec2(0, 0.0f)), m_contactListener(this) {};

		/** Default Destructor */
		virtual ~IPhysics() {};

		//set up box2d world
		virtual bool Init(IGraphic* pGraphic);

		//execute a single physics step
		virtual void Update();

		//add a body to the handler
		b2Body* AddBody(const b2BodyDef& pbody, const b2FixtureDef& fixture);

		//destroy the body from the world
		void DestroyBody(b2Body* pbody);

		//draw physics shape in scene
		virtual void DrawDebug();

		//destory a body.
		void DestoryBody(b2Body* pBody);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the Box2D world
		b2World m_world;

		//the contact listener
		ContactListener m_contactListener;

		//the physics debug draw instance
		PhysicsVisualDebug m_debugDraw;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//return a new box2d physics system
		static std::unique_ptr<IPhysics> Create() { return std::make_unique<IPhysics>(); };

		//set the gravity 
		virtual void SetGravity(V2f gravity) { m_world.SetGravity(b2Vec2(gravity.x, gravity.y)); }
	};
}