#include "../../Application/Graphic/IGraphic.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "../../Utility/MyLogger.h"
#include "../Actor/Actor.h"

bool Engine::SpriteRenderComponent::Init(tinyxml2::XMLElement * pRoot, Actor * pOwner)
{
	const char* filepath = pRoot->Attribute("filePath");
	m_pOwner = pOwner;

	if (strcmp(filepath, "0") == 0 && m_pGraphic)
	{
		return true;
	}

	this->SetSprite(filepath);

	//get the srcRect 
	const char* srcRect = pRoot->Attribute("srcRect");
	if (srcRect)
	{
		//srcRect exists
		Rect rect;
		sscanf_s(srcRect, "%d,%d,%d,%d", &rect.x, &rect.y, &rect.w, &rect.h);
		this->SetSrcRect({ rect.x, rect.y, rect.w, rect.h });
	}

	//set width & height
	this->SetWH({ pRoot->FloatAttribute("width"), pRoot->FloatAttribute("height") });
	return (m_pSprite && m_pGraphic);
}

bool Engine::SpriteRenderComponent::PostInit()
{
	m_pTransform = m_pOwner->GetComponent<TransformComponent>();
	if (!m_pTransform)
	{
		return false;
	}
	return true;
}

void Engine::SpriteRenderComponent::Render()
{
	if (m_pSprite && m_isVisible)
	{
		Rect des = { i32((m_pTransform->GetX() - m_widthHeight.x / 2) *kPixelsPerMeter),i32((m_pTransform->GetY() - m_widthHeight.y / 2) *kPixelsPerMeter), i32(m_widthHeight.x *kPixelsPerMeter), i32(m_widthHeight.y *kPixelsPerMeter) };
		m_pGraphic->Draw(m_pSprite.get(), m_srcRect, des);
	}
}

void Engine::SpriteRenderComponent::SetSprite(const char * filepath)
{
	m_pSprite = m_pGraphic->GetSprite(filepath);
}
