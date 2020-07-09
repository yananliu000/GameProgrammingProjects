#include <Tinyxml2/tinyxml2.h>
#include <Lua/lua.hpp>

#include "ActorFactory.h"
#include "../../Utility/MyLogger.h"
#include "../../Application/ApplicationLayer.h"
#include "../../Game/Component/CollisionHandlerComponent.h"
#include "../../Game/Component/PhysicsComponent.h"
#include "../../Game/Component/SpriteRenderComponent.h"
#include "../../Game/Component/TransformComponent.h"
#include "../../Game/Physics/IPhysics.h"
#include "../../Logic/IGameLayer.h"

std::shared_ptr<Engine::Actor> Engine::ActorFactory::CreateActor(const char * filepath)
{
	std::shared_ptr<Actor> pActor = std::make_shared<Actor>(m_nextActorId); 
	++m_nextActorId; 

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filepath);

	if (doc.Error())
	{
		return nullptr;
	}

	tinyxml2::XMLElement* pRoot = doc.RootElement();
	pActor->SetName(pRoot->Attribute("name")); 
	for (tinyxml2::XMLElement* pComponentXml = pRoot->FirstChildElement(); pComponentXml != nullptr;
		pComponentXml = pComponentXml->NextSiblingElement()) 
	{
		auto pComponent = CreateComponent(pComponentXml, pActor.get());
		pActor->AddComponent(std::move(pComponent));
	}

	if (!pActor->PostInit())
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Actor post-initialization fails");
		return false;
	}

	RegisterWithLua(pActor.get());

	return pActor;
}

void Engine::ActorFactory::RegisterWithLua(Actor * pActor)
{
	if (!pActor)
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Cannot register a nullptr actor with Lua");
		return;
	}

	lua_State* L = m_pLuaState;
	lua_getglobal(L, "engine"); //get engine table push it on to the stack [+1]

	lua_getfield(L, -1, "world"); // [+2]

	//create table for our actor
	lua_newtable(L); //[+3]

	//set some actor data
	lua_pushstring(L, pActor->GetName().c_str()); //[+4]
	lua_setfield(L, -2, "name"); //[+3]

	lua_pushlightuserdata(L, pActor); // [+4]
	lua_setfield(L, -2, "this"); //[+3]

	//table for our components
	lua_newtable(L); // +4

	//todo: component stuff
	for (auto& component : pActor->GetComponentMap())
	{
		component.second->RegisterWithLua(L);
	}

	lua_setfield(L, -2, "components"); //+3

	//PrintStack();
	//set the actor to the world table at [id]
	lua_seti(L, -2, pActor->GetId()); //+2

	//remove engine and world from the stack
	lua_pop(L, 2);

	//std::string script = "print(engine.world[" + std::to_string(pActor->GetId()) + "].name)";
	//std::string script = "print(engine.world[" + std::to_string(0) + "].name)";

	//luaL_dostring(L, script.c_str());
}

void Engine::ActorFactory::PrintStack()
{
	if (!m_pLuaState)
	{
		return;
	}

	int i = lua_gettop(m_pLuaState);
	printf("----------------stack dump-------------------\n");
	while (i)
	{
		int t = lua_type(m_pLuaState, i);
		switch (t)
		{
		case LUA_TSTRING:
			printf("%d: '%s'\n", i, lua_tostring(m_pLuaState, i));
			break;
		case LUA_TBOOLEAN:
			printf("%d: %s\n", i, lua_toboolean(m_pLuaState, i) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			printf("%d: %g\n", i, lua_tonumber(m_pLuaState, i));
			break;
		default:
			printf("%d: %s\n", i, lua_typename(m_pLuaState, t));
			break;
		}
		i--;
	}
}

void Engine::ActorFactory::RegisterComponentCreator(IComponent::Type type, CreateComponentFunction function)
{
	if (type != IComponent::Type::kInvalid)
	{
		m_componentCreatorMap.emplace(type, function);
	}
	else
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Component creation fails");
	}
}

std::unique_ptr<Engine::IComponent> Engine::ActorFactory::CreateComponent(tinyxml2::XMLElement * pRoot, Actor * pOwner)
{
	IComponent::Type type = IComponent::GetTypeFromElementName(pRoot->Name());

	auto creatorItr = m_componentCreatorMap.find(type);
	if (creatorItr == m_componentCreatorMap.end()) 
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Could not find the type of the component in the creationFunction map");
		return nullptr;
	}
	return creatorItr->second(pRoot, pOwner);
}

std::unique_ptr<Engine::IComponent> Engine::CreateTransform(tinyxml2::XMLElement * pData, Actor * pOwner)
{
	std::unique_ptr<Engine::TransformComponent> pTransform = std::make_unique<Engine::TransformComponent>();

	if (!pTransform->Init(pData, pOwner))
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "TransformComponent initialization fails");
		return nullptr;
	}
	return pTransform;
}

std::unique_ptr<Engine::IComponent> Engine::CreateSpriteRenderer(tinyxml2::XMLElement * pData, Actor * pOwner)
{
	std::unique_ptr<Engine::SpriteRenderComponent> pRenderer = std::make_unique<Engine::SpriteRenderComponent>();

	pRenderer->SetGraphics(ApplicationLayer::m_spGraphic);

	if (!pRenderer->Init(pData, pOwner))
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "SpriteRenderComponent initialization fails");
		return nullptr;
	}
	return pRenderer;
}

std::unique_ptr<Engine::IComponent> Engine::CreatePhysics(tinyxml2::XMLElement * pData, Actor * pOwner)
{
	std::unique_ptr<Engine::PhysicsComponent> pPhysics = std::make_unique<Engine::PhysicsComponent>();
	pPhysics->SetPhysics(ApplicationLayer::m_spPhysics);

	if (!pPhysics->Init(pData, pOwner))
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "PhysicsComponent initialization fails");
		return nullptr;
	}
	return pPhysics;
}

std::unique_ptr<Engine::IComponent> Engine::CreateCollisionHandler(tinyxml2::XMLElement * pData, Actor * pOwner)
{
	std::unique_ptr<Engine::CollisionHandlerComponent> pHandler = std::make_unique<Engine::CollisionHandlerComponent>();

	if (!pHandler->Init(pData, pOwner))
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "CollisionHandlerComponent initialization fails");
		return nullptr;
	}
	return pHandler;
}
