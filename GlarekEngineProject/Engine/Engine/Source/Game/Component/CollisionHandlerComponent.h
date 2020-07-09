#pragma once
/** \file CollisionHandlerComponent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <functional>

#include "../../Game/Component/IComponent.h"

/** \class CollisionHandlerComponent */
/** TODO: Class Purpose */
namespace Engine
{
	class CollisionHandlerComponent : public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//callback: a function to call
		typedef std::function<void(Actor*)> OverlapCallback;

		//type id
		static const Type m_kType = Type::kCollisionHandler;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		CollisionHandlerComponent() {};

		/** Default Destructor */
		~CollisionHandlerComponent() {};

		//reading data from xml
		virtual bool Init(tinyxml2::XMLElement* pRoot, Actor* pOwner) override;

		//execute OnBeginOverlap callback (if it exists)
		void BeginOverlap(Actor* pActor);

		//execute the OnEndOverlap callback (if it exists)
		void EndOverlap(Actor* pActor);

		//execute OnBeginCollision callback (if it exists)
		void BeginCollision(Actor* pActor);

		//execute OnEndCollision callback (if it exists)
		void EndCollision(Actor* pActor);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//onBeginOverlap Callback
		OverlapCallback m_onBeginOverlap;

		//onEndOverlap Callback
		OverlapCallback m_onEndOverlap;

		//onBeginOverlap Callback
		OverlapCallback m_onBeginCollision;

		//onEndOverlap Callback
		OverlapCallback m_onEndCollision;

		//true: enable overlap & false enable collision
		bool m_isTrigger;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get string: name of the component
		virtual const char* GetName() override { return "CollisionHandler"; }

		//get the type id of the component
		virtual Type GetTypeId() override { return m_kType; }

		//set OnBeginOverlap Callback
		void SetOnBeginOverlap(OverlapCallback callback) { m_onBeginOverlap = callback; }

		//set OnEndOverlap Callback
		void SetOnEndOverlap(OverlapCallback callback) { m_onEndOverlap = callback; }

		//set OnBeginCollsion Callback
		void SetOnBeginCollsion(OverlapCallback callback) { m_onBeginCollision = callback; }

		//set OnEndCollsion Callback
		void SetOnEndCollsion(OverlapCallback callback) { m_onEndCollision = callback; }

		//set value of IsTrigger
		void SetTrigget(bool isTrigger) { m_isTrigger = isTrigger; }

		//get value of IsTrigger
		bool IsTrigger() { return m_isTrigger; }
	};
}