#include "Actor.h"
#include "../../Utility/MyLogger.h"

bool Engine::Actor::PostInit()
{
	for (auto& pComponent : m_pComponentMap)
	{
		if (!pComponent.second->PostInit())
		{
			g_Logger.write(MyLogger::LogLevel::Game_Error, "Actor initialization fails");
			return false;
		}
	}
	return true;
}

void Engine::Actor::AddComponent(std::unique_ptr<IComponent> pComponent)
{
	if (pComponent) 
	{ 
		m_pComponentMap[pComponent->GetTypeId()] = std::move(pComponent); 
	}

}

void Engine::Actor::Render()
{
	SpriteRenderComponent* renderer = this->GetComponent<SpriteRenderComponent>();
	if (m_isActive && renderer)
	{
		renderer->Render();
	}
}

void Engine::Actor::Update(f32 deltaSeconds)
{
	for (auto& pComponent : m_pComponentMap)
	{
		pComponent.second->Update(deltaSeconds);
	}
}
