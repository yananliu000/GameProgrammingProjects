#pragma once
/** \file SpriteRenderComponent.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include "IComponent.h"
#include "../../Application/Texture/ISprite.h"

/** \class SpriteRenderComponent */
/** TODO: Class Purpose */

namespace Engine
{
	class IGraphic;
	class ISprite;
	class TransformComponent;

	class SpriteRenderComponent : public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//SpriteRenderComponent typeId: Type::kSpriteRenderer
		static const Type m_kType = Type::kSpriteRenderer;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SpriteRenderComponent() :m_isVisible(true) {};

		/** Default Destructor */
		~SpriteRenderComponent() {};

		//load data from xml
		virtual bool Init(tinyxml2::XMLElement* pRoot, Actor* pOwner) override;

		//set transform component pointer
		virtual bool PostInit() override;

		
		//use the m_pGraphic pointer to render the sprite 
		void Render();

		//set the width and height on the screen
		void SetWH(V2f wh) { m_widthHeight = wh; }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//sprite data reference of the actor: which can be shared by many actors
		//if an actor uses more than one sprite, make a vector of std::shared_ptr<ISprite> pair with src rect
		//and use scale for all sprites
		std::shared_ptr<ISprite> m_pSprite;

		//pass the sprite to the m_pGraphic to render 
		IGraphic* m_pGraphic;

		//get the position of the actor 
		TransformComponent* m_pTransform;

		//width and height of the sprite. similar with scale
		V2f m_widthHeight;

		//the source rect of the sprite from the sprite sheet
		Rect m_srcRect;

		//visibility of the sprite
		bool m_isVisible;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//set the IGraphics pointer
		void SetGraphics(IGraphic* pGraphic) { m_pGraphic = pGraphic; }

		//get string: name of the component
		virtual const char* GetName() { return "SpriteRenderComponent"; }

		//get the id to identity component's type
		virtual Type GetTypeId() override { return m_kType; }

		//set the rect on the source image
		void SetSrcRect(const Rect& rect) { m_srcRect = rect; }

		//get the rect on the source image
		Rect* GetSrcRect() { return &m_srcRect; }

		//set the sprite to m_pSprite
		void SetSprite(std::shared_ptr<Engine::ISprite> pSprite) { m_pSprite = pSprite; }

		//load or get sprite from sprite pool
		void SetSprite(const char* filepath);
	};
}