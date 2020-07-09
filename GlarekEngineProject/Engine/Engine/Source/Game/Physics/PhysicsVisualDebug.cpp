#include <vector>

#include "PhysicsVisualDebug.h"
#include "../../Application/Graphic/IGraphic.h"

void Engine::PhysicsVisualDebug::DrawCircle(const b2Vec2 & center, float32 radius, const b2Color & color)
{
	Color convertedColor = ConvertColor(color);
	m_pGraphic->DrawCircle(V2f(center.x, center.y), radius, convertedColor);
}

void Engine::PhysicsVisualDebug::DrawPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	Color convertedColor = ConvertColor(color);
	std::vector<V2f> verts(vertexCount);
	for (int vertIndex = 0; vertIndex < vertexCount; ++vertIndex)
	{
		verts[vertIndex] = (V2f(vertices[vertIndex].x, vertices[vertIndex].y));
	}
	m_pGraphic->DrawPolygon(verts.data(), vertexCount, convertedColor);
}

void Engine::PhysicsVisualDebug::DrawSegment(const b2Vec2 & p1, const b2Vec2 & p2, const b2Color & color)
{
	Color convertedColor = ConvertColor(color);
	m_pGraphic->DrawSegment({ p1.x, p1.y }, { p2.x, p2.y }, convertedColor);
}

void Engine::PhysicsVisualDebug::DrawRect(const b2Vec2 & wh, const b2Vec2 & position, const b2Color & color)
{
	Color convertedColor = ConvertColor(color);
	m_pGraphic->DrawRect({ wh.x, wh.y }, { position.x, position.y }, convertedColor);
}

void Engine::PhysicsVisualDebug::DrawFilledRect(const b2Vec2 & wh, const b2Vec2 & position, const b2Color & color)
{
	Color convertedColor = ConvertColor(color);
	m_pGraphic->DrawFilledRect({ wh.x, wh.y }, { position.x, position.y }, convertedColor);
}

void Engine::PhysicsVisualDebug::DrawSolidPolygon(const b2Vec2 * vertices, int32 vertexCount, const b2Color & color)
{
	DrawPolygon(vertices, vertexCount, color);
}

Color Engine::PhysicsVisualDebug::ConvertColor(const b2Color & color)
{
	return { u8(color.r * 255) , u8(color.g * 255) , u8(color.b * 255) , 255 };
}
