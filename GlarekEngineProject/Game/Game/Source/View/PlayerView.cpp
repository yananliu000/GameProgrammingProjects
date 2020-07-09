#include <sstream> 
#include <Tinyxml2/tinyxml2.h>

#include "PlayerView.h"
#include "Application/ApplicationLayer.h"
#include "Application/Texture/ITexture.h"
#include "Application/Texture/ISprite.h"
#include "Application/Graphic/IGraphic.h"
#include "Application/Audio/IAudio.h"
#include "Game/Physics/IPhysics.h"
#include "Logic/IGameLayer.h"
//#include "Utility/Common.h"
//#include "Math/Vector2.h"

using namespace tinyxml2;

void PlayerView::MapLoading(const char * filepath)
{
	//open mapset xml from filepath
	XMLDocument mapDoc;
	
	XMLError error = mapDoc.LoadFile(filepath);

	if (error != XML_SUCCESS)
	{
		return;
	}

	XMLElement* pMapRoot = mapDoc.RootElement();

	
	//get map wd and relativeFilepath: remove "stuff after the last / from filepath" (filename), then add /
	Map map;
	map.x = pMapRoot->IntAttribute("width");
	map.y = pMapRoot->IntAttribute("height");

	std::string relativeFilepath = filepath;
	relativeFilepath = relativeFilepath.substr(0, relativeFilepath.rfind('/'));
	relativeFilepath += "/";

	//load all tilesets
	for (XMLElement* pTileset = pMapRoot->FirstChildElement("tileset"); pTileset != NULL; pTileset = pMapRoot->NextSiblingElement("tileset"))
	{
		const char* tilesetFilepath = pTileset->Attribute("source");
		u32 firstgid = pTileset->IntAttribute("firstgid");

		//open tile xml from filepath
		tinyxml2::XMLDocument tileDoc;
		XMLError error = tileDoc.LoadFile((relativeFilepath + tilesetFilepath).c_str());

		if (error != XML_SUCCESS)
		{
			return;
		}

		//get tileset data
		XMLElement* pTilesetRoot = tileDoc.RootElement();
		XMLElement* pImage = pTilesetRoot->FirstChildElement("image");

		TilesetData tilesetdata;
		tilesetdata.tileWidth = pTilesetRoot->IntAttribute("tilewidth");
		tilesetdata.tileHeight = pTilesetRoot->IntAttribute("tileheight");
		tilesetdata.tileCount = pTilesetRoot->IntAttribute("tilecount");
		tilesetdata.columns = pTilesetRoot->IntAttribute("columns");
		tilesetdata.imageSource = pImage->Attribute("source");
		tilesetdata.firstgid = firstgid;

		//load tileset sprite
		m_pTilesetSprites.emplace_back(tilesetdata, m_pGraphic->GetSprite((relativeFilepath + tilesetdata.imageSource).c_str()));
	}

	//load all layers
	for (XMLElement* pLayer = pMapRoot->FirstChildElement("layer"); pLayer != NULL; pLayer = pLayer->NextSiblingElement("layer"))
	{
		LayerLoading(pLayer, map);
	}

	for (XMLElement* pObjGroup = pMapRoot->FirstChildElement("objectgroup"); pObjGroup != NULL; pObjGroup = pObjGroup->NextSiblingElement("objectgroup"))
	{
		for (XMLElement* pCollision = pObjGroup->FirstChildElement("object"); pCollision != NULL; pCollision = pCollision->NextSiblingElement("object"))
		{
			ReadCollisionObject(pCollision);
		}
	}
}

void PlayerView::ReadCollisionObject(tinyxml2::XMLElement * pCollision)
{
	std::string name = pCollision->Attribute("name");
	if (name == "test")
	{
		ReadPolygon(pCollision);
	}
	else
	{
		ReadBox(pCollision);
	}
	return;
}

void PlayerView::ReadBox(tinyxml2::XMLElement * pCollision)
{
	float x = pCollision->FloatAttribute("x") *3.75f / kPixelsPerMeter;
	float y = pCollision->FloatAttribute("y") *3.75f / kPixelsPerMeter;
	float w = pCollision->FloatAttribute("width") *3.75f / kPixelsPerMeter;
	float h = pCollision->FloatAttribute("height") *3.75f / kPixelsPerMeter;
	const char* type = pCollision->Attribute("type");
	const char* name = pCollision->Attribute("name");
	std::vector<V2f> m_points;
	m_points.push_back({ x, y });
	m_points.push_back({ x + w, y });
	m_points.push_back({ x + w, y + h });
	m_points.push_back({ x, y + h });

	//create collision object actor
	std::shared_ptr<Engine::Actor> pActor = m_pGameLayer->CreateActor("Asset\\XML\\Actor\\CollisionObject.xml");

	//physics
	Engine::PhysicsComponent* pPhysics = pActor->GetComponent<Engine::PhysicsComponent>();
	pPhysics->CreatePolygonBody(m_points, type);

	//name
	pActor->SetName(name);
}

void PlayerView::ReadPolygon(tinyxml2::XMLElement * pCollision)
{
	float originX = pCollision->FloatAttribute("x");
	float originY = pCollision->FloatAttribute("y");
	const char* type = pCollision->Attribute("type");
	const char* name = pCollision->Attribute("name");
	std::string pointsStr = pCollision->FirstChildElement("polygon")->Attribute("points");
	std::vector<V2f> m_points;
	std::stringstream stream;

	//get polygon points
	size_t lastSpaceIndex = 0;
	size_t spaceIndex = 3;
	size_t commaIndex = pointsStr.find(',', 0);
	while (lastSpaceIndex != -1)
	{
		float x;
		float y;
		std::string first, second;

		if (lastSpaceIndex == 0)
		{
			first = pointsStr.substr(lastSpaceIndex, commaIndex - lastSpaceIndex);
		}
		else
		{
			first = pointsStr.substr(lastSpaceIndex + 1, commaIndex - lastSpaceIndex - 1);
		}

		stream << first;
		stream >> x;
		stream.clear();
		stream.str(std::string());

		second = pointsStr.substr(commaIndex + 1, spaceIndex - commaIndex - 1);
		stream << second;
		stream >> y;
		stream.clear();
		stream.str(std::string());

		lastSpaceIndex = spaceIndex;
		commaIndex = pointsStr.find(',', spaceIndex + 1);
		spaceIndex = pointsStr.find(' ', commaIndex + 1);

		m_points.push_back({ (x + originX)*3.75f / kPixelsPerMeter , (y + originY)*3.75f / kPixelsPerMeter });
	}

	//create collision object actor
	std::shared_ptr<Engine::Actor> pActor = m_pGameLayer->CreateActor("Asset\\XML\\Actor\\CollisionObject.xml");

	//physics
	Engine::PhysicsComponent* pPhysics = pActor->GetComponent<Engine::PhysicsComponent>();
	pPhysics->CreatePolygonBody(m_points, type);

	//name
	pActor->SetName(name);
}

void PlayerView::LayerLoading(tinyxml2::XMLElement * pLayer, Map map)
{
	XMLElement* pLayerData = pLayer->FirstChildElement("data");

	std::string data = pLayerData->GetText();
	std::stringstream stream;

	int tileId;

	size_t lastCommaIndex = 0;
	size_t commaIndex = data.find(',', lastCommaIndex);
	float gridX = 0;
	float gridY = 0;

	while (true)
	{
		std::string number = data.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex - 1);
		stream << number;
		stream >> tileId;
		stream.clear();
		lastCommaIndex = commaIndex;

		if (tileId == 0)
		{
			commaIndex = data.find(',', lastCommaIndex + 1);
		}
		else
		{
			CreateTile(tileId, gridX, gridY);
			commaIndex = data.find(',', lastCommaIndex + 1);
		}

		++gridX;
		if (gridX >= map.x)
		{
			gridX = 0;
			++gridY;
		}

		//for the last number: read from last comma index to the end
		if (commaIndex == -1)
		{
			number = data.substr(lastCommaIndex + 1, commaIndex - lastCommaIndex - 1);
			stream << number;
			stream >> tileId;
			stream.clear();
			if (tileId != 0)
			{
				CreateTile(tileId, gridX, gridY);
			}
			break;
		}
	}
	int x = 0;
}

size_t PlayerView::GetTileSpriteIndexFromId(unsigned int Id)
{
	size_t size = m_pTilesetSprites.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (Id >= m_pTilesetSprites[i].first.firstgid)
		{
			//i is not the last map, also check next index
			if (i != size - 1)
			{
				if (Id < m_pTilesetSprites[i + 1].first.firstgid)
				{
					return i;
				}
			}
			else
			{
				return i;
			}
		}
	}
	return 0;
}

void PlayerView::CreateTile(int tileId, float gridX, float gridY)
{
	//create the tile
	std::shared_ptr<Engine::Actor> pActor = m_pGameLayer->CreateActor("Asset\\XML\\Actor\\Tile.xml");

	//set componets data
	Engine::SpriteRenderComponent* pRenderer = pActor->GetComponent<Engine::SpriteRenderComponent>();
	size_t tilesetId = GetTileSpriteIndexFromId(tileId);
	TilesetData tileset = m_pTilesetSprites[tilesetId].first;
	pRenderer->SetSprite(m_pTilesetSprites[tilesetId].second);
	pRenderer->SetWH({ 1, 1 });
	Rect subrect;
	subrect.x = ((tileId - 1) % tileset.columns) * tileset.tileWidth;
	subrect.y = ((tileId - 1) / tileset.columns) * tileset.tileHeight;
	subrect.w = tileset.tileWidth;
	subrect.h = tileset.tileHeight;

	pRenderer->SetSrcRect(subrect);

	Engine::TransformComponent* pTransform = pActor->GetComponent<Engine::TransformComponent>();
	pTransform->SetPosition({ gridX + 0.5f, gridY + 0.5f });
}



bool PlayerView::Init(Engine::ApplicationLayer * pApp)
{
	m_pAppLayer = pApp;
	m_pKeyboard = pApp->GetKeyboard();
	m_pMouse = pApp->GetMouse();
	m_pGraphic = pApp->GetGraphic();
	m_pPhysics = pApp->GetPhysics();
	m_pAudio = pApp->GetAudio();
	MapLoading("Asset/XML/Map/testmap.tmx");
	return true;
}

void PlayerView::UpdateInput()
{
	Engine::PhysicsComponent* physics = m_pPawn.lock()->GetComponent<Engine::PhysicsComponent>();
	float speed = 0.1;
	physics->SetLinearDamping(5); //friction
	//press wasd to print information
	if (m_pKeyboard->IsKeyDown(Engine::IKeyboard::Code::kCodeA))
	{
		physics->ApplyLinearImpulse(-speed, 0);
	}
	else if (m_pKeyboard->IsKeyDown(Engine::IKeyboard::Code::kCodeD))
	{
		physics->ApplyLinearImpulse(speed, 0);
	}

	if (m_pKeyboard->IsKeyDown(Engine::IKeyboard::Code::kCodeW))
	{
		physics->ApplyLinearImpulse(0, -speed);
	}
	else if (m_pKeyboard->IsKeyDown(Engine::IKeyboard::Code::kCodeS))
	{
		physics->ApplyLinearImpulse(0, speed);
	}

	if (m_pKeyboard->IsKeyPressed(Engine::IKeyboard::Code::kCodeQ))
	{
		std::shared_ptr<Engine::Actor> pActor = m_pPawn.lock();
		m_pGameLayer->CreateDanceProcess(pActor);
	}
}

void PlayerView::ViewScene()
{
	m_pGraphic->StartDrawing({ 169, 169, 169, 250 });

	for (auto& actor : m_pGameLayer->GetActors())
	{
		actor.second->Render();
	}
	m_pPhysics->DrawDebug();
	m_pGraphic->EndDrawing();
}


