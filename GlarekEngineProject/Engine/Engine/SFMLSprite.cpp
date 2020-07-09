#ifdef _SFML

#include "Source/Application/Texture/SFMLSprite.h"
#include "Source/Application/Texture/ITexture.h"

bool Engine::SFMLSprite::Init(ITexture * pTexture)
{
	m_pSprite = new sf::Sprite; 
	m_pSprite->setTexture(*reinterpret_cast<sf::Texture*> (pTexture->GetNativeTexture())); 
	return m_pSprite != nullptr;
}

bool Engine::SFMLSprite::Init(const char * filepath)
{
	sf::Texture texture;
	texture.loadFromFile(filepath);
	m_pSprite = new sf::Sprite;
	m_pSprite->setTexture(texture);
	return m_pSprite != nullptr;
}
#endif