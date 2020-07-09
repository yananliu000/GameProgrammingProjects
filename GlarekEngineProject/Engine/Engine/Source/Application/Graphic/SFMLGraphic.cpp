#ifdef _SFML
#include <SFML/Graphics.hpp>

#include "SFMLGraphic.h"

#include "../Window/IWindow.h"
#include "../Texture/SFMLSprite.h"
#include "../Texture/SFMLTexture.h"
#include "../../Utility/MyLogger.h"

//Warning: sfml-graphic-s-d works for debug x64 
// -d not

using Engine::SFMLGraphic;
sf::RenderWindow* SFMLGraphic::m_spRenderer = nullptr;

bool Engine::SFMLGraphic::Init(IWindow * pWindow)
{
	//get sfml window from iwindow
	m_spRenderer = reinterpret_cast<sf::RenderWindow*>(pWindow->GetNativeWindow());
	
	if (!m_spRenderer || !m_spRenderer->isOpen())
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Fail loading SFML_pRenderer.");
	}
	return true;
}

void Engine::SFMLGraphic::StartDrawing(Color baseColor)
{
	m_spRenderer->clear(sf::Color(baseColor.red, baseColor.green, baseColor.blue, baseColor.alpha));
}

void Engine::SFMLGraphic::EndDrawing()
{
	m_spRenderer->display();
}

bool Engine::SFMLGraphic::Draw(ISprite * pSprite, Rect & srcRect, Rect & desRect)
{
	//get sfmlsprite
	sf::Sprite* pToDraw = reinterpret_cast<sf::Sprite*>(pSprite->GetNativeSprite());

	//set the rects
	pToDraw->setTextureRect(sf::IntRect(i32(srcRect.x), i32(srcRect.y), i32(srcRect.w), i32(srcRect.h)));
	pToDraw->setPosition(sf::V2f(float(desRect.x),float(desRect.y)));
	pToDraw->setScale(sf::V2f((desRect.w / float(srcRect.w)), float(desRect.h / float(srcRect.h))));

	//pToDraw->setScale(sf::V2f(1,1));
	//sfml render
	m_spRenderer->draw(*pToDraw);
	
	return true;
}

std::shared_ptr<Engine::ISprite> Engine::SFMLGraphic::GetSprite(const char * filepath)
{
	//check sprite map
	auto spriteMapItr = m_pSpriteMap.find(filepath);
	if (spriteMapItr == m_pSpriteMap.end()) //not in sprite map
	{
		//check texture map
		auto textureMapItr = m_pTextureMap.find(filepath);
		if (textureMapItr == m_pTextureMap.end()) //neither in texture map
		{
			std::unique_ptr<SFMLTexture> pTexture = std::make_unique<SFMLTexture>();

			if (pTexture->Init(filepath))
			{
				//load the new texture
				textureMapItr = m_pTextureMap.emplace(filepath, std::move(pTexture)).first;
			}
			else
			{
				//fail loading texture
				g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail loading SFML_Texture.");
				return nullptr;
			}
		}

		//create the sprite use the texture
		//if find texture succeeded: textureMapItr is the right texture
		//if failed: is the new created texture
		std::shared_ptr<SFMLSprite> pSprite = std::make_shared<SFMLSprite>();
		if (!pSprite->Init(textureMapItr->second.get()))
		{
			g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail loading SFML_Sprite.");
		
		}
		spriteMapItr = m_pSpriteMap.emplace(filepath, std::move(pSprite)).first;
	}
	//if have it in the sprite map: return the right sprite
	//if not: return the new created sprite
	return spriteMapItr->second;
}

void Engine::SFMLGraphic::DrawCircle(const V2f center, f32 radius, const Color color)
{
	sf::CircleShape shape(radius);
	shape.setOrigin({center.x, center.y});
	shape.setOutlineColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	m_spRenderer->draw(shape);
}

void Engine::SFMLGraphic::DrawPolygon(const V2f* points, i32 pointCount, const Color color)
{
	sf::ConvexShape convex;
	convex.setPointCount(pointCount);

	for (int i = 0; i < pointCount; ++i)
	{
		convex.setPoint(i, {points[i].x* kPixelsPerMeter,points[i].y* kPixelsPerMeter });
	}
	convex.setOutlineColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	convex.setOutlineThickness(1);
	convex.setFillColor(sf::Color(color.red, color.green, color.blue, 50));

	m_spRenderer->draw(convex);
}

void Engine::SFMLGraphic::DrawSegment(const V2f p1, const V2f p2, const Color color)
{
	sf::Vertex line[] =
	{
		sf::Vertex({p1.x, p1.y}),
		sf::Vertex({p2.x, p2.y})
	};
	line->color = sf::Color(color.red, color.green, color.blue, color.alpha);
	m_spRenderer->draw(line, 2, sf::Lines);
}

void Engine::SFMLGraphic::DrawSegments(const V2f * points, i32 pointCount, const Color color)
{
	g_Logger.write(MyLogger::LogLevel::System_Error, "SFML does not support DrawSegments");
}

void Engine::SFMLGraphic::DrawRect(const V2f wh, const V2f position, const Color color)
{
	sf::RectangleShape rectangle({ wh.x, wh.y });
	rectangle.setPosition({ position.x, position.y });
	rectangle.setOutlineColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	m_spRenderer->draw(rectangle);
}

void Engine::SFMLGraphic::DrawFilledRect(const V2f wh, const V2f position, const Color color)
{
	sf::RectangleShape rectangle({ wh.x, wh.y });
	rectangle.setPosition({ position.x, position.y });
	rectangle.setOutlineColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	rectangle.setFillColor(sf::Color(color.red, color.green, color.blue, color.alpha));
	m_spRenderer->draw(rectangle);
}

void Engine::SFMLGraphic::DrawPoint(const V2f position, const Color color)
{
	g_Logger.write(MyLogger::LogLevel::System_Error, "SFML does not support DrawPoint");
}

void Engine::SFMLGraphic::DrawPoints(const std::vector<V2f> position, i32 pointCount, const Color color)
{
	g_Logger.write(MyLogger::LogLevel::System_Error, "SFML does not support DrawPoints");
}

V2f Engine::SFMLGraphic::GetMousePosition()
{
	auto p = sf::Mouse::getPosition(*m_spRenderer);
	return V2f(p.x, p.y);
}

Color Engine::SFMLGraphic::GetRenderDrawColor()
{
	g_Logger.write(MyLogger::LogLevel::System_Error, "SFML does not support GetRenderDrawColor");
	return Color();
}

void Engine::SFMLGraphic::SetRenderDrawColor(Color* color)
{
	g_Logger.write(MyLogger::LogLevel::System_Error, "SFML does not support SetRenderDrawColor");
}

#endif