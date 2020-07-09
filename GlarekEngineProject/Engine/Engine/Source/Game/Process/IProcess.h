#pragma once
/** \file IProcess.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>
#include <functional>

#include "../../Utility/Common.h"


/** \class IProcess */
/** TODO: Class Purpose */
namespace Engine
{
	class Actor;
	class IProcess
	{
	public:
		typedef std::function<void()> Callback;

		enum class EState
		{
			kUnitialized, //default state of process
			kRunning, //process is being around 
			kPaused, //freeze the process
			kSucceeded, //the process just complete
			kFailed, //the process fail to complete
			kAborted //the process is asked to stop
		};
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		//not creat and init in the same frame: 1. avoid infinite loop, 2. make it be around for the correct duration
		IProcess() : m_state(EState::kUnitialized) {};

		//destructor: clean and end
		virtual ~IProcess() {};

		//update the process if it's krunning
		virtual void Update(f32 deltaSeconds) = 0;

		//init the process
		virtual bool Init() { return true; }

		//set pProcess as the process' child process
		void AttachChild(std::shared_ptr<IProcess> pProcess) { m_pChildProcess = pProcess; }

		//return the process' child process and set m_pChildProcess to null
		std::shared_ptr<IProcess> RemoveChild();

		//return whether the process has a child process
		bool HasChild() { return m_pChildProcess != nullptr; }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		EState m_state;
		Callback m_succeedCallback; //! function to call when succeed
		Callback m_failCallback; //! function to call when fail
		Callback m_abortCallback; //! function to call when abort
		std::shared_ptr<IProcess> m_pChildProcess; //child process will be added into the manager when the process succeeds

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get string name of the process for logging
		virtual const char* GetName() = 0;

		//change the current state of the process to target state
		void ChangeState(EState kNewState) { m_state = kNewState; }

		//get the current state of the process
		EState GetState() { return m_state; }

		//set Succeeded/Failed/Aborted callback based on the given state
		DLLEXP void SetCallback(EState state, Callback callback);

		//execute Succeeded/Failed/Aborted callback based on the given state
		void ExecuteCallback(EState state);

		//get the pointer of the process' owner
		Actor* GetOwner();

		//set pActor as the process' owner
		void SetOwner(std::shared_ptr<Actor> pActor) { m_pOwner = pActor; }

		//return whether the process is running /paused 
		bool IsAlive();

	protected:
		std::weak_ptr<Engine::Actor> m_pOwner;

	};
}