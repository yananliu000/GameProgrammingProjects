#include "SDLWindow.h"
#if _SDL
using Engine::SDLWindow;

SDLWindow::SDLWindow() :m_isInitialized(false), m_pSFMLWindow(nullptr, nullptr)
{
	
}

SDLWindow::~SDLWindow()
{
	m_pSFMLWindow = nullptr;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);//audio and vedio systems are seperate, so we only quit video subsystem here. 
	SDL_Quit();
}

bool Engine::SDLWindow::Init(const char * pName, u32 width, u32 height)
{

	if (SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		return false;
	}

	m_pSFMLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
		SDL_CreateWindow(pName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
		&SDL_DestroyWindow);

	if (!m_pSFMLWindow)
	{
		return false;
	}

	m_isInitialized = true;

	return true;
}

Engine::IKeyboard::Code Engine::SDLWindow::ConvertToCode(u32 key)
{
	if (key >= SDLK_a && key <= SDLK_z)
		return static_cast<IKeyboard::Code>(key - SDLK_a + IKeyboard::Code::kCodeA);

	else if (key >= SDLK_0 && key <= SDLK_9)
		return static_cast<IKeyboard::Code>(key - SDLK_0 + IKeyboard::Code::kCode0);

	else if (key == SDLK_ESCAPE)
		return IKeyboard::Code::kCodeEscape;

	else if (key == SDLK_RETURN)
		return IKeyboard::Code::kCodeEnter;

	else if (key == SDLK_RIGHT)
		return IKeyboard::Code::kCodeRightArrow;

	else if (key == SDLK_LEFT)
		return IKeyboard::Code::kCodeLeftArrow;

	else if (key == SDLK_UP)
		return IKeyboard::Code::kCodeUpArrow;

	else if (key == SDLK_DOWN)
		return IKeyboard::Code::kCodeDownArrow;

	else if (key == SDLK_SPACE)
		return IKeyboard::Code::kCodeSpacebar;

	return IKeyboard::Code::kCodeMax;
}

Engine::IMouse::Button Engine::SDLWindow::ConvertToButton(u32 button)
{
	if (button == SDL_BUTTON_LEFT)
		return IMouse::Button::kButtonLeft;

	if (button == SDL_BUTTON_RIGHT)
		return IMouse::Button::kButtonRight;

	return IMouse::Button::kButtonNum;
}

bool Engine::SDLWindow::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		//quit
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			return false;

		//press or release any key
		if (m_pKeyboard && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
		{
			Engine::IKeyboard::Code code = ConvertToCode(event.key.keysym.sym);
			m_pKeyboard->SetKeyState(code, event.type == SDL_KEYDOWN); //if is keydown true, keyup false
		}

		//click or release any mouse button
		if (m_pMouse && (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP))
		{
			Engine::IMouse::Button button = ConvertToButton(event.button.button);
			m_pMouse->SetButtonState(button, event.type == SDL_MOUSEBUTTONDOWN); //button down true, button up false
		}	
	}

	return true;
}

void * Engine::SDLWindow::GetNativeWindow() const
{
	return m_pSFMLWindow.get();
}
#endif