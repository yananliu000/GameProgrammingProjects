#include "ProcessManager.h"
#include "../../Utility/MyLogger.h"

void Engine::ProcessManager::Update(f32 deltaSeconds)
{

	for (size_t index = 0; index < m_pProcesses.size(); ++index)
	{
		auto pProcess = m_pProcesses[index];

		switch (pProcess->GetState())
		{
			//state: kUnitialized=> Init, true: change state to running, false: erase
		case Engine::IProcess::EState::kUnitialized:
			if (!pProcess->Init())
			{
				m_pProcesses.erase(m_pProcesses.begin() + index);
			}
			else
			{
				pProcess->ChangeState(IProcess::EState::kRunning);
			}
			break;

			//state: abort=> callonAbort, erase
		case Engine::IProcess::EState::kAborted:
			pProcess->ExecuteCallback(IProcess::EState::kAborted);
			m_pProcesses.erase(m_pProcesses.begin() + index);
			break;

			//state: fail=> callonFail, erase
		case Engine::IProcess::EState::kFailed:
			pProcess->ExecuteCallback(IProcess::EState::kFailed);
			m_pProcesses.erase(m_pProcesses.begin() + index);
			break;

			//state: pause=> skip
		case Engine::IProcess::EState::kPaused:
			break;

			//state: running=> update
		case Engine::IProcess::EState::kRunning:
			pProcess->Update(deltaSeconds);
			break;

			//state: succeed=> callonSuccess, if it has child, add its child to pool, then erase it
		case Engine::IProcess::EState::kSucceeded:
		{
			// Success callback
			pProcess->ExecuteCallback(IProcess::EState::kSucceeded);

			//add to erase pool
			m_pProcesses.erase(m_pProcesses.begin() + index);

			if (pProcess->HasChild())
			{
				m_pProcesses.emplace_back(pProcess->RemoveChild());
			}
		}
		break;

		//shouldnt go here
		//erase
		default:
			g_Logger.write(MyLogger::LogLevel::Game_Warning, "process manager found process with an unrecognizable state");
			m_pProcesses.erase(m_pProcesses.begin() + index);
			break;
		}

		//next process
		++index;
	}
}

void Engine::ProcessManager::AttachProcess(std::shared_ptr<IProcess> pProcess)
{
	m_pProcesses.emplace_back(pProcess);
}

void Engine::ProcessManager::ReplaceProcess(std::shared_ptr<IProcess> pProcess)
{
	for (auto& process : m_pProcesses)
	{
		if (process->GetOwner() == pProcess->GetOwner() &&
			std::string(process->GetName()) == pProcess->GetName())
		{
			process = pProcess;
		}
	}
	AttachProcess(pProcess);
}

void Engine::ProcessManager::AbortAllProcesses()
{
	for (auto& pProcess : m_pProcesses)
	{
		if (pProcess->IsAlive())
		{
			pProcess->ExecuteCallback(IProcess::EState::kAborted); //call abort callback
			pProcess->ChangeState(IProcess::EState::kAborted); //set state to kAbort
		}
	}
}
