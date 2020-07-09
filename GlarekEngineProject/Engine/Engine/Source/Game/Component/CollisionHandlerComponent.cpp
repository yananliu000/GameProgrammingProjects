#include "CollisionHandlerComponent.h"

bool Engine::CollisionHandlerComponent::Init(tinyxml2::XMLElement * pRoot, Actor * pOwner)
{
	m_pOwner = pOwner;
	return true;
}

void Engine::CollisionHandlerComponent::BeginOverlap(Actor * pActor)
{
	if (m_onBeginOverlap && m_isTrigger)
	{
		m_onBeginOverlap(pActor);
	}
}

void Engine::CollisionHandlerComponent::EndOverlap(Actor * pActor)
{
	if (m_onEndOverlap  && m_isTrigger)
	{
		m_onEndOverlap(pActor);
	}
}

void Engine::CollisionHandlerComponent::BeginCollision(Actor * pActor)
{
	if (m_onBeginCollision && !m_isTrigger)
	{
		m_onBeginCollision(pActor);
	}
}

void Engine::CollisionHandlerComponent::EndCollision(Actor * pActor)
{
	if (m_onEndCollision && !m_isTrigger)
	{
		m_onEndCollision(pActor);
	}
}
