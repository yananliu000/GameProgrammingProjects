#include <Lua/lua.hpp>

#include "IGameLayer.h"
#include "../Utility/MyLogger.h"
#include "../Application/ApplicationLayer.h"
#include "../Game/Event/CreateActorEvent.h"
#include "../Game/Event/DefeatEnemyEvent.h"
#include "../Game/Event/ConsumeItemEvent.h"
#include "../Game/Event/PickUpItemEvent.h"
#include "../Game/Event/AttackEvent.h"
#include "../Game/Actor/Actor.h"

using Engine::IGameLayer;

bool Engine::IGameLayer::InitViews()
{
	//lua
	CreateLuaState();
	m_actorFactory.SetLuaState(m_pLuaState);

	for (auto& pView : m_pViews)
	{
		if (!pView->Init(m_pAppLayer))
		{
			return false;
		}
	}

	
	return true;
}

void Engine::IGameLayer::CreateLuaState()
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);

	//set up the initial table structure 
	//engine table
	lua_createtable(m_pLuaState, 0, 10); //[+1]

	//world table
	lua_createtable(m_pLuaState, 0, 100); //[+2]

	//add world to engine
	lua_setfield(m_pLuaState, -2, "world"); //[+1]

	//add our engine to the global table
	lua_setglobal(m_pLuaState, "engine"); //[+0]

	//luaL_dostring(m_pLuaState, "print(engine.world)");

}

void Engine::IGameLayer::DefineFactoryComponentCreators()
{
	m_actorFactory.RegisterComponentCreator(IComponent::Type::kTransform, &Engine::CreateTransform);
	m_actorFactory.RegisterComponentCreator(IComponent::Type::kSpriteRenderer, &Engine::CreateSpriteRenderer);
	m_actorFactory.RegisterComponentCreator(IComponent::Type::kPhysics, &Engine::CreatePhysics);
	m_actorFactory.RegisterComponentCreator(IComponent::Type::kCollisionHandler, &Engine::CreateCollisionHandler);
}

Engine::Actor * Engine::IGameLayer::GetActor(u32 id)
{
	//"It is possible for Lua to have a reference to a dead Actor."
	auto actorItr = m_pActorMap.find(id);
	if (actorItr != m_pActorMap.end())
	{
		return actorItr->second.get();
	}

	return nullptr;
}


void Engine::IGameLayer::RegisterEngineEvents()
{
	m_eventDispatcher.AddEventListener(CreateActorEvent::m_kEventId, [this](IEvent* pEvent)
	{
		CreateActorEvent* pCreateEvent = static_cast<CreateActorEvent*>(pEvent);
		CreateActor(pCreateEvent->GetXmlFilepath());
	});
}

void Engine::IGameLayer::RegisterGameEvents()
{
	m_eventDispatcher.AddEventListener(PickUpItemEvent::m_kEventId, [this](IEvent* pEvent)
	{
		CreateActorEvent* pCastEvent = static_cast<CreateActorEvent*>(pEvent);
		CreateActor(pCastEvent->GetXmlFilepath());
	});

	m_eventDispatcher.AddEventListener(ConsumeItemEvent::m_kEventId, [this](IEvent* pEvent)
	{
		ConsumeItemEvent* pCastEvent = static_cast<ConsumeItemEvent*>(pEvent);
	});

	m_eventDispatcher.AddEventListener(DefeatEnemyEvent::m_kEventId, [this](IEvent* pEvent)
	{
		ConsumeItemEvent* pCastEvent = static_cast<ConsumeItemEvent*>(pEvent);
	});

	m_eventDispatcher.AddEventListener(AttackEvent::m_kEventId, [this](IEvent* pEvent)
	{
		ConsumeItemEvent* pCastEvent = static_cast<ConsumeItemEvent*>(pEvent);
	});
}

Engine::IGameLayer::~IGameLayer()
{
	lua_close(m_pLuaState);
}

bool Engine::IGameLayer::Init(Engine::ApplicationLayer * pAppLayer)
{
	RegisterEngineEvents();

	m_pAppLayer = pAppLayer;
	m_physicsAccumulator = 0;
	if (!InitViews())
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "View initialization fails");
	}
	return true;
}

void Engine::IGameLayer::Update(f64 deltaSeconds)
{
	//solution for debugging mode's long delta time problem
#if _DEBUG
	if (deltaSeconds >= 1.0f)
	{
		deltaSeconds = 0;
	}
#endif
	//lua
	//print engine.world[3].components
	//engine.world[3].components.TransformComponent

	//luaL_dostring(pstate, "print('hello, Lua!')");

	//std::string script = "print(engine.world[0].components.TransformComponent).Move(engine.world[0].components.TransformComponent, 0.1,0)";

	//luaL_dostring(m_pLuaState, script.c_str());

	int result = luaL_dofile(m_pLuaState, "Asset\\Scripts\\test.lua");
	if (result != LUA_OK)
	{
		g_Logger.write(MyLogger::LogLevel::Game_Error, "Lua Error");
		m_actorFactory.PrintStack();
	}
	//update views
	for (auto& pView : m_pViews)
	{
		pView->UpdateInput();
	}

	//events
	m_eventDispatcher.ProcessEvents();

	//processes
	m_processManager.Update((f32)deltaSeconds);

	//physics
	
	m_physicsAccumulator += deltaSeconds;
	if (m_physicsAccumulator >= kPhyTimestep)
	{
		m_pAppLayer->GetPhysics()->Update();
		m_physicsAccumulator -= kPhyTimestep;
	}

	//update actors
	for (auto& actorPair : m_pActorMap)
	{
		actorPair.second->Update((f32)deltaSeconds);
	}

	//dislay views
	for (auto& pView : m_pViews)
	{
		pView->ViewScene();
	}
}

void Engine::IGameLayer::AddView(std::unique_ptr<IView> pView)
{
	m_pViews.emplace_back(std::move(pView));
}

std::shared_ptr<Engine::Actor> Engine::IGameLayer::CreateActor(const char * xmlFilepath)
{
	std::shared_ptr<Actor> pActor = m_actorFactory.CreateActor(xmlFilepath);
	m_pActorMap.emplace(pActor->GetId(), pActor);
	return pActor;
}

void Engine::IGameLayer::EndFrame()
{
	//if there is no actors waiting to be destoryed 
	//return
	if (m_pDeferDestroySet.size() == 0)
		return;

	//for each actor waiting tp be destoryed
	for (auto& pActor : m_pDeferDestroySet)
	{
		//find where is the actor
		auto actorItr = m_pActorMap.find(pActor->GetId());
		if (actorItr != m_pActorMap.end()) //didnt find it, jump; find it, erase 
			m_pActorMap.erase(actorItr);
	}
	//after finish destroying, clear the pool
	m_pDeferDestroySet.clear();
}