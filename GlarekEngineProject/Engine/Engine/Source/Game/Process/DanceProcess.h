#pragma once
//dance process: press Q to dance 
//play music
//1.play sound effect
//move left: obj's spcace + 1s
//move up: obj's spcace + 1s
//move right: obj's spcace + 1s
//move down: obj's spcace + 1s

//2.
//change the actor's texture to blue 

//3. succeedCallback:
//spawn 4 small blues around the actor

//4.
//the 4 small blues begin patrol: move + delay

#include "IProcess.h"

/** \file DanceProcess.h */
/** TODO: File Purpose */
// Created by Billy Graban



/** \class DanceProcess */
/** TODO: Class Purpose */
namespace Engine
{
	class TransformComponent; //change position

	class DanceProcess : public IProcess
	{
		
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DanceProcess(float velocity, float intervalTime) : velocity(velocity), m_intervalTime(intervalTime), m_speed(0.f, 0.f) {}


		/** Default Destructor */
		~DanceProcess() {};

		//init the process
		DLLEXP virtual bool Init() override;

		//update: move and change directions
		DLLEXP virtual void Update(f32 deltaSeconds) override;

		
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		enum EDanceMove
		{
			kInitialized,
			kMoveLeft,
			kMoveUp,
			kMoveRight,
			kMoveDown,
			kMoveNum
		};

		//the Dance move state of the process
		EDanceMove m_danceMove;

		//the time between changing direction
		float m_intervalTime;

		//record the passed time
		float m_timer;

		//how fast the actor will move
		float velocity;

		//the current speed of the actor 
		V2f m_speed;

		//obj's transform component to change positin of the object, will also update its physicsComponent's position
		TransformComponent* m_pTransformComponent;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//return a string of the process' name
		virtual const char* GetName() override { return "DanceProcess"; }

	};
}