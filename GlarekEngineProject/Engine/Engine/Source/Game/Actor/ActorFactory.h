#pragma once
/** \file ActorFactory.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <functional>
#include <unordered_map>

#include "..\..\Utility\Common.h"
#include "..\Component\IComponent.h"
#include "Actor.h"

/** \class ActorFactory */
/** TODO: Class Purpose */
struct lua_State;
namespace Engine
{
	class Actor;
	class IGameLayer;
	class ActorFactory
	{
		//typedef the pointer of a function take a xml element* and an actor* tp create a specific component
		typedef std::function<std::unique_ptr<IComponent>(tinyxml2::XMLElement*, Actor*)> CreateComponentFunction;

	protected:
		IGameLayer* m_pGameLogic;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		ActorFactory(IGameLayer* pgameLogic) { m_pGameLogic = pgameLogic; }

		/** Default Destructor */
		~ActorFactory() {};

		//create actor based on the filepath xml data
		std::shared_ptr<Actor> CreateActor(const char* filepath);

		//add (type, craetion function) for the CreateComponentFunction map
		void RegisterComponentCreator(IComponent::Type type, CreateComponentFunction function);

		void RegisterWithLua(Actor * pActor);

		void PrintStack();
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//actor id counter
		u32 m_nextActorId;

		//a map stores component creation functions
		std::unordered_map<IComponent::Type, CreateComponentFunction> m_componentCreatorMap;
		lua_State* m_pLuaState;
		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		//pass the component info of the component
		std::unique_ptr<IComponent> CreateComponent(tinyxml2::XMLElement* pRoot, Actor* pOwner);

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		void SetLuaState(lua_State* pstate) { m_pLuaState = pstate; }


	};

	//public creation functions for Transform component
	std::unique_ptr<Engine::IComponent> CreateTransform(tinyxml2::XMLElement* pData, Actor* pOwner);

	//public creation functions for SpriteRenderer component
	std::unique_ptr<Engine::IComponent> CreateSpriteRenderer(tinyxml2::XMLElement* pData, Actor* pOwner);

	//public creation functions for Physics component
	std::unique_ptr<Engine::IComponent> CreatePhysics(tinyxml2::XMLElement* pData, Actor* pOwner);

	//public creation functions for CollisionHandler component
	std::unique_ptr<Engine::IComponent> CreateCollisionHandler(tinyxml2::XMLElement* pData, Actor* pOwner);

}