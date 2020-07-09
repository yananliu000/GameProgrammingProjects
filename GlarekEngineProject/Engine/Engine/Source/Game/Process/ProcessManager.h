#pragma once
/** \file ProcessManager.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <vector>

#include "..\..\Utility\Common.h"
#include "IProcess.h"

namespace Engine
{
	/** \class ProcessManager */
	/** TODO: Class Purpose */
	class ProcessManager
	{
		std::vector<std::shared_ptr<IProcess>> m_pProcesses;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ProcessManager() {};

		/** Default Destructor */
		~ProcessManager() { AbortAllProcesses(); }

		//< update all live process
		void Update(f32 deltaSeconds);

		//< add a process into the manager
		DLLEXP void AttachProcess(std::shared_ptr<IProcess> pProcess);

		//< use the process to replace the same actor's same name process
		//< not found: just attach the process
		void ReplaceProcess(std::shared_ptr<IProcess> pProcess);

		//< abort all paused and running processes
		DLLEXP void AbortAllProcesses();
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
