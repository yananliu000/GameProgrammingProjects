#pragma once
/** \file IGraphic.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>
#include <vector>

#include "../../Utility/Common.h"
#include "../../Math/Vector2.h"

namespace Engine
{
	/** \class IGraphic */
	/** TODO: Class Purpose */
	class IWindow;
	class ISprite;

	class IGraphic
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		IGraphic() {}

		/** Default Destructor */
		virtual ~IGraphic() {}

		//init graphics system
		virtual bool Init(IWindow* pWindow) = 0;

		//render the backrgound color
		virtual void StartDrawing(Color baseColor) = 0;

		//present the renderer
		virtual void EndDrawing() = 0;

		//create a new graphics system and return it
		static std::unique_ptr<IGraphic> Create();

		//get thre sprite under the filepath, if havent been loaded, load it
		virtual std::shared_ptr<ISprite> GetSprite(const char* filepath) = 0;

		//draw the sprite
		virtual bool Draw(ISprite* pSprite, Rect& srcRect, Rect& desRect) = 0;

		//draw a circle
		virtual void DrawCircle(const V2f center, f32 radius, const Color color) = 0;

		//draw a polygon
		virtual void DrawPolygon(const V2f* points, i32 pointCount, const Color color) = 0;

		//draw a line
		virtual void DrawSegment(const V2f p1, const V2f p2, const Color color) = 0;

		//draw lines
		virtual void DrawSegments(const V2f* points, i32 pointCount, const Color color) = 0;

		//draw a rect
		virtual void DrawRect(const V2f wh, const V2f position, const Color color) = 0;

		//draw a filled rect
		virtual void DrawFilledRect(const V2f wh, const V2f position, const Color color) = 0;

		//draw a point
		virtual void DrawPoint(const V2f position, const Color color) = 0;

		//draw points
		virtual void DrawPoints(const std::vector<V2f> position, i32 pointCount, const Color color) = 0;

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
		virtual V2f GetMousePosition() = 0;

		//use this function to get the color used for drawing operations (Rect, Line and Clear).
		virtual Color GetRenderDrawColor() = 0;

		//use this function to set the color used for drawing operations (Rect, Line and Clear).
		virtual void SetRenderDrawColor(Color* color) = 0;

	};
}