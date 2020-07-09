#ifdef _SDL
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_surface.h"
#include "../Window/IWindow.h"
#include "../Texture/SDLTexture.h"
#include "../Texture/SDLSprite.h"
#include "SDLGraphic.h"
#include "../../Utility/MyLogger.h"

using Engine::SDLGraphic;

SDL_Renderer* SDLGraphic::m_spRenderer = nullptr;

bool SDLGraphic::Init(Engine::IWindow * pWindow)
{
	//get sdl_window from iwindow 
	SDL_Window* pSdlWindow = reinterpret_cast<SDL_Window*>(pWindow->GetNativeWindow());

	//init prenderer
	m_spRenderer = SDL_CreateRenderer(pSdlWindow, -1, SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC |
		SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	if (!m_spRenderer)
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Fail loading SDL_pRenderer.");
	}
	i32 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	bool imgInitialized = (IMG_Init(imgFlags) == imgFlags);
	if (!imgInitialized)
	{
		g_Logger.write(MyLogger::LogLevel::System_Error, "Fail loading SDL_image.");

	}

	// Enable alpha blending
	SDL_SetRenderDrawBlendMode(m_spRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

	return imgInitialized && m_spRenderer;
}

void SDLGraphic::StartDrawing(Color baseColor)
{
	SDL_SetRenderDrawColor(m_spRenderer, baseColor.red, baseColor.green, baseColor.blue, baseColor.alpha);
	SDL_RenderClear(m_spRenderer);
}

void SDLGraphic::EndDrawing()
{
	SDL_RenderPresent(m_spRenderer);
}

bool SDLGraphic::Draw(Engine::ISprite * pSprite, Rect & srcRect, Rect & desRect)
{
	//get sdlsprite
	SDL_Texture * pToDraw = reinterpret_cast<SDL_Texture*>(pSprite->GetNativeSprite());

	//construct the rects
	SDL_Rect srcRectSDL = { i32(srcRect.x),i32(srcRect.y), i32(srcRect.w),i32(srcRect.h) };
	SDL_Rect desRectSDL = { i32(desRect.x),i32(desRect.y),i32(desRect.w),i32(desRect.h) };

	//sdl render copy
	SDL_RenderCopy(m_spRenderer, pToDraw, &srcRectSDL, &desRectSDL);

	return true;
}

std::shared_ptr<Engine::ISprite> SDLGraphic::GetSprite(const char * filepath)
{
	//check sprite map
	auto spriteMapItr = m_pSpriteMap.find(filepath);
	if (spriteMapItr == m_pSpriteMap.end()) //not in sprite map
	{
		//check texture map
		auto textureMapItr = m_pTextureMap.find(filepath);
		if (textureMapItr == m_pTextureMap.end()) //neither in texture map
		{
			std::unique_ptr<SDLTexture> pTexture = std::make_unique<SDLTexture>();
			if (pTexture->Init(filepath))
			{
				//load the new texture
				textureMapItr = m_pTextureMap.emplace(filepath, std::move(pTexture)).first;
			}
			else
			{
				//fail loading texture
				g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail loading SDL_Texture.");
				return nullptr;
			}
		}

		//create the sprite use the texture
		//if find texture succeeded: textureMapItr is the right texture
		//if failed: is the new created texture
		std::shared_ptr<SDLSprite> pSprite = std::make_shared<SDLSprite>();
		if (!pSprite->Init(textureMapItr->second.get()))
		{
			g_Logger.write(MyLogger::LogLevel::Game_Error, "Fail loading SDL_Sprite.");

		}
		spriteMapItr = m_pSpriteMap.emplace(filepath, pSprite).first;
	}
	//if have it in the sprite map: return the right sprite
	//if not: return the new created sprite
	return spriteMapItr->second;
}

void SDLGraphic::DrawCircle(const V2f center, f32 radius, const Color color)
{
	V2f centerCopy = center;
	centerCopy *= f32(kPixelsPerMeter);
	radius *= f32(kPixelsPerMeter);

	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	i32 x = i32(radius - 1);
	i32 y = 0;
	i32 tx = 1;
	i32 ty = 1;
	i32 err = tx - i32(radius * 2); // shifting bits left by 1 effectively

								 // doubles the value. == tx - diameter
	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x + x), i32(centerCopy.y - y));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x + x), i32(centerCopy.y + y));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x - x), i32(centerCopy.y - y));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x - x), i32(centerCopy.y + y));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x + y), i32(centerCopy.y - x));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x + y), i32(centerCopy.y + x));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x - y), i32(centerCopy.y - x));
		SDL_RenderDrawPoint(m_spRenderer, i32(centerCopy.x - y), i32(centerCopy.y + x));

		if (err <= 0)
		{
			y++;
			err += ty;
			ty += 2;
		}
		if (err > 0)
		{
			x--;
			tx += 2;
			err += i32(tx - (radius * 2));
		}
	}
}

void SDLGraphic::DrawPolygon(const V2f* points, i32 pointCount, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	std::vector<SDL_Point> sdlpoints;

	for (i32 i = 0; i < pointCount; ++i)
	{
		sdlpoints.push_back({ i32(points[i].x * kPixelsPerMeter), i32(points[i].y * kPixelsPerMeter) });
	}
	sdlpoints.push_back({ i32(points[0].x * kPixelsPerMeter), i32(points[0].y * kPixelsPerMeter) });

	SDL_RenderDrawLines(m_spRenderer, sdlpoints.data(), pointCount + 1); //pass the beginning of sdl point vector
}

void SDLGraphic::DrawSegment(const V2f p1, const V2f p2, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawLine(m_spRenderer, i32(p1.x * kPixelsPerMeter), i32(p1.y * kPixelsPerMeter), i32(p2.x * kPixelsPerMeter), i32(p2.y * kPixelsPerMeter));
}

void Engine::SDLGraphic::DrawSegments(const V2f * points, i32 pointCount, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	std::vector<SDL_Point> sdlpoints;

	for (i32 i = 0; i < pointCount; ++i)
	{
		sdlpoints.push_back({ i32(points[i].x * kPixelsPerMeter), i32(points[i].y * kPixelsPerMeter) });
	}
	SDL_RenderDrawLines(m_spRenderer, sdlpoints.data(), pointCount + 1); //pass the beginning of sdl point vector
}


void SDLGraphic::DrawRect(const V2f wh, const V2f position, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	SDL_Rect rect = { i32(position.x * kPixelsPerMeter), i32(position.y * kPixelsPerMeter), i32(wh.x * kPixelsPerMeter), i32(wh.y * kPixelsPerMeter) };
	SDL_RenderDrawRect(m_spRenderer, &rect);
}

void SDLGraphic::DrawFilledRect(const V2f wh, const V2f position, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	SDL_Rect rect = { i32(position.x  * kPixelsPerMeter), i32(position.y  * kPixelsPerMeter), i32(wh.x  * kPixelsPerMeter), i32(wh.y  * kPixelsPerMeter) };
	SDL_RenderFillRect(m_spRenderer, &rect);
}

void Engine::SDLGraphic::DrawPoint(const V2f position, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	SDL_RenderDrawPoint(m_spRenderer, position.x, position.y);
}

void Engine::SDLGraphic::DrawPoints(const std::vector<V2f> position, i32 pointCount, const Color color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color.red, color.green, color.blue, color.alpha);
	std::vector<SDL_Point> sdlpoints;

	for (i32 i = 0; i < pointCount; ++i)
	{
		sdlpoints.push_back({ i32(position[i].x * kPixelsPerMeter), i32(position[i].y * kPixelsPerMeter) });
	}
	SDL_RenderDrawPoints(m_spRenderer, sdlpoints.data(), pointCount);
}

V2f Engine::SDLGraphic::GetMousePosition()
{
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x,&y);
	return V2f(float(x), float(y));
}

Color Engine::SDLGraphic::GetRenderDrawColor()
{
	Color color;
	SDL_GetRenderDrawColor(m_spRenderer, &color.red, &color.green, &color.blue, &color.alpha);
	return color;
}

void Engine::SDLGraphic::SetRenderDrawColor(Color* color)
{
	SDL_SetRenderDrawColor(m_spRenderer, color->red, color->green, color->blue, color->alpha);
}

#endif // _SDLc