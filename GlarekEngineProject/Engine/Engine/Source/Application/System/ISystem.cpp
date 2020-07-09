#include "ISystem.h"
#include"WINSystem.h"

/*
#if _WIN32
#include"WINSystem.h"
#else
#include "IOSSystem.h"
#endif
*/
std::shared_ptr<Engine::ISystem> Engine::ISystem::Create()
{
	return std::make_shared<WINSystem>();

	/*
#if _WIN32
	// Return new windows system
	return std::make_shared<WINSystem>();
#elif _IOS
	return std::make_shared<IOSSystem>();
#endif
*/
}


std::unique_ptr<Engine::IWindow> Engine::ISystem::CreateSystemWindow(const char * pTitle, u32 width, u32 height)
{
#ifdef _SFML
	std::unique_ptr<IWindow> pWindow(new SFMLWindow());
#else 
	std::unique_ptr<IWindow> pWindow(new SDLWindow());
#endif
	if (pWindow->Init(pTitle, width, height))
	{
		return pWindow;
	}
	return nullptr;
}

