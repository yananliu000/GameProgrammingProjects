#include "IPhysics.h"
#include "../../Utility/MyLogger.h"
#include "../../Game/Component/CollisionHandlerComponent.h"

bool Engine::IPhysics::Init(IGraphic * pGraphic)
{
	m_world.SetDebugDraw(&m_debugDraw);
	m_debugDraw.Init(pGraphic);
	m_debugDraw.SetFlags(0x0001);
	m_world.SetContactListener(&m_contactListener);
	return true;
}

void Engine::IPhysics::Update()
{
	m_contactListener.ClearContacts();
	m_world.Step(f32(kPhyTimestep), 10, 2);
	m_contactListener.HandleCollisions();
}

b2Body * Engine::IPhysics::AddBody(const b2BodyDef & pbody, const b2FixtureDef & fixture)
{
	b2Body* pBody = m_world.CreateBody(&pbody);
	pBody->CreateFixture(&fixture);
	return pBody;
}

void Engine::IPhysics::DestroyBody(b2Body * pbody)
{
	m_world.DestroyBody(pbody);
}

void Engine::IPhysics::DrawDebug()
{
	m_world.DrawDebugData();
}

void Engine::IPhysics::DestoryBody(b2Body * pBody)
{
	m_world.DestroyBody(pBody);
}
