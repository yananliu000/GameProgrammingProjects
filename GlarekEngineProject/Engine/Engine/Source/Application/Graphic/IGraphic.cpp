#include "IGraphic.h"
#include "../Window/IWindow.h"
//SDL, SFML handles input, window creation, image loading and ...
//Grapphics like OpenGl, directX: rendering
//SDL + OpenGl
//SFML + SFML
#ifdef _SFML
#include "SFMLGraphic.h"
#else
#include "SDLGraphic.h"
#endif
using Engine::IGraphic;

std::unique_ptr<IGraphic> IGraphic::Create()
{
#if _SFML
	return std::unique_ptr<IGraphic>(new SFMLGraphic());

#else
	return std::unique_ptr<IGraphic>(new SDLGraphic());

#endif
}

