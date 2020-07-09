#pragma once
/** \file PlayerView.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>

#include "Application/View/IView.h"
#include "Utility/Common.h"
#include "Game/Actor/Actor.h"

/** \class PlayerView */
/** TODO: Class Purpose */
namespace Engine
{
	class IGraphic;
	class ISprite;
	class IPhysics;
	class TransformComponent;
	class IGameLayer;
	class ApplicationLayer;
	class IKeyboard;
	class IMouse;
	class IAudio;
}

class PlayerView
	: public Engine::IView
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //
	

	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	PlayerView(Engine::IGameLayer* pOwningLayer) 
		: m_pGameLayer(pOwningLayer)
		{}

	//initialization
	bool Init(Engine::ApplicationLayer* pApp) override;
	
	//update user input
	void UpdateInput() override;
	
	//display the view
	void ViewScene() override;

	/** Default Destructor */
	~PlayerView() {};

	void SetPawn(std::weak_ptr<Engine::Actor> pPawn) { m_pPawn = pPawn; }

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	Engine::IGraphic*			m_pGraphic;
	Engine::IGameLayer*			m_pGameLayer;
	Engine::ApplicationLayer*	m_pAppLayer;
	Engine::IPhysics*			m_pPhysics;
	Engine::IAudio*				m_pAudio;
	Engine::IKeyboard*			m_pKeyboard;
	Engine::IMouse*				m_pMouse;

	std::weak_ptr<Engine::Actor> m_pPawn;

	struct TilesetData
	{
		u8 tileWidth;
		u8 tileHeight;
		u16 columns;
		u32 tileCount;
		u32 firstgid;
		const char* imageSource;
	};

	struct Map
	{
		u32 x;
		u32 y;
	};

	typedef std::vector<std::pair<TilesetData, std::shared_ptr<Engine::ISprite>>> TilesetSpriteVec;
	TilesetSpriteVec m_pTilesetSprites;

	//float m_movespeed;
	//float m_maxspeed;
	//float m_acceleration;
	//float m_deceleration;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	void MapLoading(const char* filepath);

	void LayerLoading(tinyxml2::XMLElement* pLayer, Map map);

	size_t GetTileSpriteIndexFromId(unsigned int Id);

	void CreateTile(int tileId, float gridX, float gridY);

	void ReadCollisionObject(tinyxml2::XMLElement* pCollision);

	void ReadPolygon(tinyxml2::XMLElement * pCollision);

	void ReadBox(tinyxml2::XMLElement * pCollision);

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};