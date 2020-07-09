#pragma once
/** \file Actor.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <unordered_map>
#include <memory>

#include "../../Utility/Common.h"
#include "../Component/SpriteRenderComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/CollisionHandlerComponent.h"
#include "../Component/PhysicsComponent.h"

/** \class Actor */
/** TODO: Class Purpose */
namespace Engine
{
	#define ComponentMap std::unordered_map<IComponent::Type, std::unique_ptr<IComponent>>
	class IGraphic;

	class Actor
	{
	private:
		//special id number ecch actor has
		u32 m_actorId;

		//is the actor active
		bool m_isActive;

		//map of all components of the actor
		ComponentMap m_pComponentMap;

		//string name of the actor: forlogging
		std::string m_name;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		enum class ActorType
		{
			kDefault,
			kAActor,
			kAPawn,
			kACharacter,
			kAPlayerController
		};

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		Actor(u32 id) : m_actorId(id), m_isActive(true) {};

		/** Default Destructor */
		virtual ~Actor() {};

		//post init all componets of the actor
		virtual bool PostInit();

		//add a component to the actor
		void AddComponent(std::unique_ptr<IComponent> pComponent);

		//render the component
		DLLEXP void Render();

		//update all components
		void Update(f32 deltaSeconds);

		ComponentMap& GetComponentMap() { return m_pComponentMap; }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the specific component
		template<typename T>
		T* GetComponent();

		//get the actor id
		u32 GetId() const { return m_actorId; }

		//get string: name of the actor
		const std::string& GetName() const { return m_name; }

		//is actor active?
		bool IsActive() const { return m_isActive; }

		//set actor's name
		void SetName(const char* name) { m_name = name; }

		virtual void Attack(Actor* pTarget) {}
	};

	template <typename T>
	T* Actor::GetComponent()
	{
		if (m_pComponentMap.size() == 0)
		{
			return nullptr;
		}

		auto componentItr = m_pComponentMap.find(T::m_kType);

		if (componentItr != m_pComponentMap.end())
		{
			return static_cast<T*>(componentItr->second.get());
		}
		return nullptr;
	}
}