#include <Lua/lua.hpp>

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "../Actor/Actor.h"

bool Engine::TransformComponent::Init(tinyxml2::XMLElement * pRoot, Actor * pOwner)
{
	m_position.x = pRoot->FloatAttribute("x");
	m_position.y = pRoot->FloatAttribute("y");
	m_pOwner = pOwner;
	return true;
}

bool Engine::TransformComponent::PostInit()
{
	m_pPhysics = m_pOwner->GetComponent<PhysicsComponent>();

	if (m_pPhysics)
	{
		m_pPhysics->SetPosition(m_position.x, m_position.y);
	}

	return true;
}

void Engine::TransformComponent::Move(float x, float y)
{
	m_position.x = x;
	m_position.y = y;

	if (m_pPhysics)
		m_pPhysics->SetPosition(x, y);
}

void Engine::TransformComponent::MoveToward(float x, float y)
{
	m_position.x += x;
	m_position.y += y;

	if (m_pPhysics)
		m_pPhysics->SetPosition(x, y);
}

void Engine::TransformComponent::RegisterWithLua(lua_State * pState)
{
	lua_newtable(pState);
	//assumes that the component of the owning actor table is on the top of the stack
	lua_pushlightuserdata(pState, this); //  + 1
	lua_setfield(pState, -2, "this"); // 0 

	lua_pushcfunction(pState, Lua::TransformComponent_Move); // + 1
	lua_setfield(pState, -2, "Move"); // - 1

	lua_pushcfunction(pState, Lua::TransformComponent_MoveToward); // + 1
	lua_setfield(pState, -2, "MoveToward"); //-1

	lua_setfield(pState, -2, GetName()); //set -2 index to be the transform component

}

int Lua::TransformComponent_Move(lua_State * pState)
{
	//(this, x, y) order of passing y x this 
	Engine::TransformComponent* pComponent = reinterpret_cast<Engine::TransformComponent*>(lua_touserdata(pState, -3));
	f32 xDelta = (f32)lua_tonumber(pState, -2);
	f32 yDelta = (f32)lua_tonumber(pState, -1);

	lua_pop(pState, 3);

	pComponent->Move(xDelta, yDelta);
	return 0;
}

int Lua::TransformComponent_MoveToward(lua_State * pState)
{
	Engine::TransformComponent* pComponent = reinterpret_cast<Engine::TransformComponent*>(lua_touserdata(pState, -3));
	f32 xDelta = (f32)lua_tonumber(pState, -2);
	f32 yDelta = (f32)lua_tonumber(pState, -1);

	lua_pop(pState, 3);

	pComponent->MoveToward(xDelta, yDelta);
	return 0;
}
