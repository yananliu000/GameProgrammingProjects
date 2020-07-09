#pragma once
/** \file IGameLayer.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <map>
#include <memory>
#include <vector>
#include <Zlib/zlib.h>

#include "../Utility/Common.h"
#include "../Application/View/IView.h"
#include "../Game/Actor/Actor.h"
#include "../Game/Actor/ActorFactory.h"
#include "../Game/Event/EventDispatcher.h"
#include "../Game/Event/CreateActorEvent.h"
#include "../Game/Process/ProcessManager.h"

#define ZLIB_WINAPI

/** \class IGameLayer */
/** TODO: Class Purpose */
struct lua_State;

namespace Engine
{
	class IView;
	class ApplicationLayer;
	class Actor;
	class IGameLayer
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DLLEXP IGameLayer():m_actorFactory(this) {};

		/** Default Destructor */
		DLLEXP virtual ~IGameLayer();

		//initialization
		DLLEXP virtual bool Init(Engine::ApplicationLayer* pAppLayer);

		//the overall update function: deltaseconds is the the time passed since last frame. many functions needs it to update. 
		DLLEXP virtual void Update(f64 deltaSeconds);

		//add a new view to the list
		DLLEXP virtual void AddView(std::unique_ptr<IView> pView);

		//create actor, getting data from xml file
		DLLEXP virtual std::shared_ptr<Actor> CreateActor(const char* xmlFilepath);

		//clear actors in destroy pool
		DLLEXP virtual void EndFrame();

		//add the actor into th destory pool
		void AddDestroyActor(std::shared_ptr<Actor> pActor) { m_pDeferDestroySet.emplace_back(pActor); }

		//add all compoments into actor factory
		DLLEXP virtual void DefineFactoryComponentCreators();

		//virtual function that registers all engine - wide events
		DLLEXP virtual void RegisterEngineEvents();

		//empty virtual function that can be overridden for game-specific events
		DLLEXP virtual void RegisterGameEvents();

	protected:
		//manager of all processes
		ProcessManager m_processManager;

		//contains and dispatches events each frame
		EventDispatcher m_eventDispatcher;

		//applicationLayer pointer
		ApplicationLayer* m_pAppLayer;

		//init all views
		bool InitViews();

		lua_State* m_pLuaState;
		void CreateLuaState();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//timer for deciding when to step physics
		f64 m_physicsAccumulator;

		typedef std::map<u32, std::shared_ptr<Actor>> ActorMap;

		//store actors in a map with unique ids
		ActorMap m_pActorMap;

		// a vector of views. 
		std::vector<std::unique_ptr<IView>> m_pViews;

		//factory to create actors
		ActorFactory m_actorFactory;

		//destory actors pool
		std::vector <std::shared_ptr<Actor>> m_pDeferDestroySet;

		//stores the most recently created actor for access later
		std::shared_ptr<Actor> m_pMostRecentlyCreatedActor;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the game's name
		virtual const char* GetGameName() const = 0;

		//get the actor just created
		std::shared_ptr<Actor> GetMostRecentlyCreatedActor() { return m_pMostRecentlyCreatedActor; }

		//get map of all actors
		ActorMap& GetActors() { return m_pActorMap; }

		//get actor of the id
		Actor* GetActor(u32 id);

		//get the event dispatcher
		EventDispatcher& GetEventDispatcher() { return m_eventDispatcher; }

		//get the process manager
		ProcessManager& GetProcessManager() { return m_processManager; }

		//process
		DLLEXP virtual void CreateDelayProcess(std::shared_ptr<Engine::Actor> pActor) = 0;

		DLLEXP virtual void CreateMoveProcess(std::shared_ptr<Engine::Actor> pActor) = 0;

		DLLEXP virtual void CreateDanceProcess(std::shared_ptr<Engine::Actor> pActor) = 0;
	};
}