#pragma once
/** \file SDLGraphic.h */
/** TODO: File Purpose */
// Created by Billy Graban

#ifdef _SDL
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "./IGraphic.h"
#include "../Texture/ITexture.h"
#include "../Texture/ISprite.h"
namespace Engine
{
	/** \class SDLGraphic */
	/** TODO: Class Purpose */
	class SDLGraphic
		: public IGraphic
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//global access point to the sdl_renderer
		static SDL_Renderer* m_spRenderer;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		SDLGraphic() {};

		/** Default Destructor */
		~SDLGraphic() {};

		//init sdl graphics system
		virtual bool Init(class IWindow* pWindow) override;

		//render the backrgound color
		virtual void StartDrawing(Color baseColor) override;

		//present the renderer
		virtual void EndDrawing() override;

		//draw the sprite
		virtual bool Draw(ISprite* pSprite, Rect& srcRect, Rect& desRect) override;

		//get thre sprite under the filepath, if havent been loaded, load it
		virtual std::shared_ptr<ISprite> GetSprite(const char* filepath) override;

		//draw a circle
		void DrawCircle(const V2f center, f32 radius, const Color color) override;

		//draw a polygon
		void DrawPolygon(const V2f* points, i32 pointCount, const Color color) override;

		//draw a line
		void DrawSegment(const V2f p1, const V2f p2, const Color color) override;

		//draw lines
		virtual void DrawSegments(const V2f* points, i32 pointCount, const Color color) override;

		//draw a rect
		void DrawRect(const V2f wh, const V2f position, const Color color) override;

		//draw a filled rect
		void DrawFilledRect(const V2f wh, const V2f position, const Color color) override;

		//draw a point
		virtual void DrawPoint(const V2f position, const Color color) override;
		//draw points
		virtual void DrawPoints(const std::vector<V2f> position, i32 pointCount, const Color color) override;
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the window to render to 
		SDL_Window* m_pWindow;

		//all textures currently in memory on the graphics card
		std::unordered_map<std::string, std::unique_ptr<ITexture>> m_pTextureMap;

		//a map of single sprites associated with each texture on the graphics card
		std::unordered_map<std::string, std::shared_ptr<ISprite>> m_pSpriteMap;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		V2f GetMousePosition() override;

		//use this function to get the color used for drawing operations (Rect, Line and Clear).
		virtual Color GetRenderDrawColor() override;

		//use this function to set the color used for drawing operations (Rect, Line and Clear).
		virtual void SetRenderDrawColor(Color* color) override;

	};
}
#endif
//