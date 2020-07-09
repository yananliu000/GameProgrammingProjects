#include "ContactListener.h"
#include "../../Game/Component/CollisionHandlerComponent.h"
#include "../../Game/Actor/Actor.h"
#include "../../Utility/MyLogger.h"
#include "IPhysics.h"


void Engine::ContactListener::BeginContact(b2Contact * pContact)
{
	CollisionData collisionA;
	CollisionData collisionB;

	collisionA.m_pActor = static_cast<Actor*>(pContact->GetFixtureA()->GetBody()->GetUserData());
	collisionB.m_pActor = static_cast<Actor*>(pContact->GetFixtureB()->GetBody()->GetUserData());

	if (!collisionA.m_pActor || !collisionB.m_pActor)
	{
		return;
	}

	collisionA.m_pOther = collisionB.m_pActor;
	collisionB.m_pOther = collisionA.m_pActor;

	collisionA.m_isContact = true;
	collisionB.m_isContact = true;

	m_collisions.push_back(collisionA);
	m_collisions.push_back(collisionB);
}

void Engine::ContactListener::EndContact(b2Contact * pContact)
{
	CollisionData collisionA;
	CollisionData collisionB;

	collisionA.m_pActor = static_cast<Actor*>(pContact->GetFixtureA()->GetBody()->GetUserData());
	collisionB.m_pActor = static_cast<Actor*>(pContact->GetFixtureB()->GetBody()->GetUserData());

	if (!collisionA.m_pActor || !collisionB.m_pActor)
	{
		return;
	}

	collisionA.m_pOther = collisionB.m_pActor;
	collisionB.m_pOther = collisionA.m_pActor;

	collisionA.m_isContact = false;
	collisionB.m_isContact = false;

	m_collisions.push_back(collisionA);
	m_collisions.push_back(collisionB);
}

void Engine::ContactListener::HandleCollisions()
{
	for (auto& collision : m_collisions)
	{
		auto handler = collision.m_pActor->GetComponent<CollisionHandlerComponent>();
		if (handler)
		{
			if (collision.m_isContact)
			{
				handler->BeginOverlap(collision.m_pOther);
			}
			else
			{
				handler->EndOverlap(collision.m_pOther);
			}
		}
	}
}
