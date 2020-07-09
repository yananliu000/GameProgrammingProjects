#pragma once
/** \file IComponent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <Tinyxml2/tinyxml2.h>
#include <string>

#include "../../Utility/Common.h"

/** \class IComponent */
/** TODO: Class Purpose */
struct lua_State;
namespace Engine
{
	class Actor;
	class IComponent
	{
	protected:
		Actor* m_pOwner;

	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//<new components:
		//<1. static const m_kType
		//<2. add a case: GetTypeFromElementName: take string name, return the IComponent::type
		//<3. add a glocal creat function for the component
		enum class Type
		{
			kInvalid,
			kTransform,
			kSpriteRenderer,
			kPhysics,
			kCollisionHandler,
		};

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IComponent() {};

		/** Default Destructor */
		virtual ~IComponent() {};

		//read data from xml
		virtual bool Init(tinyxml2::XMLElement* pRoot, Actor* pOwner) = 0;

		//post init the component
		virtual bool PostInit() { return true; }

		//update the component
		virtual void Update(f32 deltaSeconds) { }

		virtual void RegisterWithLua(lua_State* pState) {};

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
		//get string: the name of the component
		virtual const char* GetName() = 0;

		//take string name, get the corresponding type of the component
		static IComponent::Type GetTypeFromElementName(const std::string& name);

		//get the type id of the component
		virtual Type GetTypeId() = 0;
	};
}