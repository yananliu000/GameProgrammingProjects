#include "IProcess.h"

void Engine::IProcess::SetCallback(EState state, Callback callback)
{
	switch (state)
	{
	case Engine::IProcess::EState::kSucceeded:
		m_succeedCallback = callback;
		break;
	case Engine::IProcess::EState::kFailed:
		m_failCallback = callback;
		break;
	case Engine::IProcess::EState::kAborted:
		m_abortCallback = callback;
		break;
	default:
		break;
	}
}

void Engine::IProcess::ExecuteCallback(EState state)
{
	switch (state)
	{
	case Engine::IProcess::EState::kSucceeded:
	{
		if (m_succeedCallback)
			m_succeedCallback();
	}
	break;
	case Engine::IProcess::EState::kFailed:
	{
		if (m_failCallback)
			m_failCallback();
	}
	break;
	case Engine::IProcess::EState::kAborted:
	{
		if (m_abortCallback)
			m_abortCallback();
	}
	break;
	default:
		break;
	}
}

Engine::Actor * Engine::IProcess::GetOwner()
{
	auto pActor = m_pOwner.lock();
	if (pActor)
		return pActor.get();
	return nullptr;
}

std::shared_ptr<Engine::IProcess> Engine::IProcess::RemoveChild()
{
	auto pChild = m_pChildProcess;
	m_pChildProcess = nullptr;
	return m_pChildProcess;
}

bool Engine::IProcess::IsAlive()
{
	return (m_state == EState::kPaused || m_state == EState::kRunning);
}
