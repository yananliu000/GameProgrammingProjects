#pragma once
/** \file DelayProcess.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include "IProcess.h"

namespace Engine
{
	/** \class DelayProcess */
	/** TODO: Class Purpose */
	class DelayProcess : public IProcess
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		//constructor: delay f32 seconds
		DelayProcess(f32 delay) : m_delayTime(delay) {};

		//destructor
		~DelayProcess() {};

		//update timer and check conditons
		virtual void Update(f32 deltaSeconds) override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//time to delay
		f32 m_delayTime;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//return a string of the process' name
		virtual const char* GetName() override { return "DelayProcess"; }

	};

	//when the timer finishes, process succeed
	inline void DelayProcess::Update(f32 deltaSeconds)
	{
		m_delayTime -= deltaSeconds;
		if (m_delayTime <= 0.f)
		{
			this->ChangeState(IProcess::EState::kSucceeded);
		}
	}
}