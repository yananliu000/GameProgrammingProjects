#pragma once
/** \file TransformComponent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include "IComponent.h"
#include "../../Utility/Common.h"

/** \class TransformComponent */
/** TODO: Class Purpose */
namespace Lua
{
	int TransformComponent_Move(lua_State* pState);
	int TransformComponent_MoveToward(lua_State* pState);

}


namespace Engine
{
	class PhysicsComponent;

	class TransformComponent : public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//transformComponent typeId: Type::kTransform
		static const Type m_kType = Type::kTransform;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		TransformComponent(){};

		/** Default Destructor */
		~TransformComponent(){};

		//read date from xml
		virtual bool Init(tinyxml2::XMLElement* pRoot, Actor* pOwner) override;

		//set PhysicsComponent pointer
		virtual bool PostInit() override;

		//absolute space, move to the position, update in physicsComponent
		GLUA()
		void Move(float x, float y);

		//object space, move based on present position, update in physicsComponent
		//glua test
		GLUA() 
		void MoveToward(float x, float y);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//actor's position date
		V2f m_position;

		//override physics position when player moves in transform : SetPosition()
		PhysicsComponent* m_pPhysics;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get string: name of the component
		virtual const char* GetName() { return "TransformComponent"; }

		//get actor's x position
		f32 GetX() const { return m_position.x; }

		//get actor's y position
		f32 GetY() const { return m_position.y; }

		//get actor's position
		V2f GetPosition() const { return m_position; }

		//set actor's position
		void SetPosition(V2f position) { m_position = position; }

		//get the component's type id
		virtual Type GetTypeId() override { return m_kType; }

		void RegisterWithLua(lua_State* pState) override;

	};
}