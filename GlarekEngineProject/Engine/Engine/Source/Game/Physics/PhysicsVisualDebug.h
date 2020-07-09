#pragma once
/** \file PhysicsVisualDebug.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include "Box2D/Box2D.h"
#include "../../Utility/Common.h"

/** \class PhysicsVisualDebug */
/** TODO: Class Purpose */
namespace Engine
{
	class IGraphic;

	class PhysicsVisualDebug : public b2Draw
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		PhysicsVisualDebug() {};

		/** Default Destructor */
		~PhysicsVisualDebug() {};

		//set IGraphics pointer
		bool Init(IGraphic* pGraphics) { m_pGraphic = pGraphics; return true; }

		//draw a circle
		void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

		//draw a polygon
		void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

		//draw a line
		void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

		//draw a rect
		void DrawRect(const b2Vec2& wh, const b2Vec2& position, const b2Color& color);

		//draw a filled rect
		void DrawFilledRect(const b2Vec2& wh, const b2Vec2& position, const b2Color& color);

		//draw a point
		virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override {}; //unfinished

		//draw a transform
		virtual void DrawTransform(const b2Transform& xf) override {}; //unfinished

		//draw a solid circle
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override {}; //unfinished

		//draw a solid polygon
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		
		//convert color from b2Color to Color
		Color ConvertColor(const b2Color& color);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//IGraphics pointer used to draw
		IGraphic* m_pGraphic;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		

	};
}