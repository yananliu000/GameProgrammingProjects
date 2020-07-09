#include "PhysicsComponent.h"
#include "../Actor/Actor.h"
#include "../../Game/Physics/IPhysics.h"
#include "../../Game/Component/TransformComponent.h"

Engine::PhysicsComponent::~PhysicsComponent()
{
	if (m_pBody)
	{
		m_pPhysics->DestroyBody(m_pBody);
	}
}

void Engine::PhysicsComponent::Addbody(b2BodyDef * bodyDef, b2FixtureDef * fixDef)
{
	m_pBody = m_pPhysics->AddBody(*bodyDef, *fixDef);
	if (!m_pBody)
	{
		return;
	}
	m_pBody->SetUserData(m_pOwner);
}

bool Engine::PhysicsComponent::Init(tinyxml2::XMLElement * pRoot, Actor * pOwner)
{
	//owner
	m_pOwner = pOwner;

	//body type
	std::string bodyType = pRoot->Attribute("bodyType");
	b2BodyDef bodyDef;
	if (!ParseBodyDef(bodyType, bodyDef))
	{
		return false;
	}

	//gravity
	if (pRoot->Attribute("gravity", "off"))
	{
		bodyDef.gravityScale = 0;
	}

	
	//fixture & shape
	b2FixtureDef fixDef;
	tinyxml2::XMLElement* pShapeData = pRoot->FirstChildElement("shape");
	const char* shapeType = pShapeData->Attribute("type");

	//sensor
	if (pRoot->Attribute("sensor", "true"))
	{
		fixDef.isSensor = true;
	}

	if (shapeType == std::string("circle"))
	{
		b2CircleShape circle;
		circle.m_radius = pShapeData->FloatAttribute("radius");
		fixDef.shape = &circle;
		Addbody(&bodyDef, &fixDef);
	}
	else if (shapeType == std::string("box"))
	{
		b2PolygonShape polygon;
		polygon.SetAsBox(pShapeData->FloatAttribute("halfWidth"), pShapeData->FloatAttribute("halfHeight"));
		fixDef.shape = &polygon;
		Addbody(&bodyDef, &fixDef);
	}
	else if (shapeType == std::string("polygon"))
	{
		//unfinished
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

bool Engine::PhysicsComponent::PostInit()
{
	m_pTransform = m_pOwner->GetComponent<TransformComponent>();

	if (m_pBody && m_pTransform)
	{
		m_pBody->SetTransform(b2Vec2(m_pTransform->GetX(), m_pTransform->GetY()), 0);
	}
	return true;
}

void Engine::PhysicsComponent::Update(f32 deltaSeconds)
{
	b2Vec2 pos = m_pBody->GetPosition();
	if (m_pTransform)
	{
		m_pTransform->SetPosition({ pos.x , pos.y });
	}
}

void Engine::PhysicsComponent::ApplyLinearImpulse(f32 x, f32 y)
{
	m_pBody->ApplyLinearImpulse(b2Vec2(x, y), m_pBody->GetLocalCenter(), true);
}

bool Engine::PhysicsComponent::CreatePolygonBody(std::vector<V2f>& points, const std::string & type)
{
	b2BodyDef bodyDef;
	if (!ParseBodyDef(type, bodyDef))
	{
		return false;
	}

	b2FixtureDef fixDef;
	b2PolygonShape polygon;

	std::vector<b2Vec2> vertices;
	for (size_t i = 0; i < points.size(); ++i)
	{
		vertices.push_back(b2Vec2(points[i].x, points[i].y));
	}
	polygon.Set(&vertices[0], int32(points.size()));
	fixDef.shape = &polygon;
	Addbody(&bodyDef, &fixDef);
	return true;
}

bool Engine::PhysicsComponent::ParseBodyDef(const std::string & option, b2BodyDef & outBodyDef)
{
	if (option == "static")
	{
		outBodyDef.type = b2_staticBody;
	}
	else if (option == "kinematic")
	{
		outBodyDef.type = b2_kinematicBody;
	}
	else if (option == "dynamic")
	{
		outBodyDef.type = b2_dynamicBody;
	}
	else
	{
		return false;
	}
	return true;
}

void Engine::PhysicsComponent::SetPosition(float x, float y)
{
	if (m_pBody)
	{
		m_pBody->SetTransform(b2Vec2(x, y), m_pBody->GetAngle());
	}
}

V2f Engine::PhysicsComponent::GetPosition()
{
	b2Vec2 pos = m_pBody->GetPosition();
	return V2f(pos.x, pos.y);
}
