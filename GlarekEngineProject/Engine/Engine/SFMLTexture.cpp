#ifdef _SFML

#include "Source/Application/Texture/SFMLSprite.h"
#include "Source/Application/Texture/SFMLTexture.h"

bool Engine::SFMLTexture::Init(const char * filepath)
{
	m_ptexture = new sf::Texture; 
	m_ptexture->loadFromFile(filepath);
	return m_ptexture != nullptr;
}
#endif