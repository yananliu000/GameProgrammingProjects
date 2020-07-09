#pragma once
/** \file PhysicsComponent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include <Box2D/Box2D.h>
#include <vector>

#include "../../Utility/Common.h"
#include "IComponent.h"

/** \class PhysicsComponent */
/** TODO: Class Purpose */
namespace Engine
{
	class IPhysics;
	class TransformComponent;

	class PhysicsComponent : public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//physicsComponent id: Type::kPhysics
		static const Type m_kType = Type::kPhysics;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		PhysicsComponent() {};

		/** Default Destructor */
		~PhysicsComponent();

		//add body into
		void Addbody(b2BodyDef* bodyDef, b2FixtureDef* fixDef);

		//read data from xml
		virtual bool Init(tinyxml2::XMLElement* pRoot, Actor* pOwner) override;

		//get transfrom component from the owner actor
		virtual bool PostInit() override;

		//update the transform position
		virtual void Update(f32 deltaSeconds) override;

		//get string: name of the component
		virtual const char* GetName() { return "PhysicsComponet"; }

		//apply a force to the object
		DLLEXP void ApplyLinearImpulse(f32 x, f32 y);

		//for create collision polygons of tiled
		DLLEXP bool CreatePolygonBody(std::vector<V2f>& points, const std::string& type);
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//box2d body: a structure contains data, including position etc.
		b2Body* m_pBody;

		//the physics world 
		IPhysics* m_pPhysics;

		//actor's TransformComponent used to parse actor position with physics component
		TransformComponent* m_pTransform;

		
		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		//helper function for parsing Box2D body definitions: physics states 
		bool ParseBodyDef(const std::string& option, b2BodyDef& outBodyDef);
	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//set the physics world 
		void SetPhysics(IPhysics* pPhyisics) { m_pPhysics = pPhyisics; }

		//set the position of the obj: b2body
		void SetPosition(float x, float y);

		//change the linear damping
		void SetLinearDamping(f32 damping) { m_pBody->SetLinearDamping(damping); }

		//set the linear velocity
		void SetLinearVelocity(V2f  velocity) { m_pBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y)); }

		//get the typeId of the component				
		virtual Type GetTypeId() override { return m_kType; }		//< Returns the TypeId of the component

		//get position from box2d body 
		V2f  GetPosition();
	};
}