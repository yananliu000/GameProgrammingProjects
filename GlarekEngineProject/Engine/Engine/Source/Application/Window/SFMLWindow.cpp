#ifdef  _SFML


#include "SFMLWindow.h"
using namespace Engine;

SFMLWindow::SFMLWindow():m_isInitialized(false), m_pSFMLWindow(nullptr)
{
}

SFMLWindow::~SFMLWindow()
{
	m_pSFMLWindow->close();
}

bool Engine::SFMLWindow::Init(const char * pName, u32 width, u32 height)
{
	// Declare and create a new window
	sf::RenderWindow* pSFMLWindow = new sf::RenderWindow(sf::VideoMode(width, height), pName);
	m_pSFMLWindow = std::unique_ptr<sf::RenderWindow>(pSFMLWindow);

	if (!m_pSFMLWindow)
	{
		return false;
	}
	else
	{
		m_isInitialized = true;
		return m_isInitialized;
	}
}

IKeyboard::Code Engine::SFMLWindow::ConvertToCode(u32 key)
{
	if (key >= sf::Keyboard::A && key <= sf::Keyboard::Z)
		return static_cast<IKeyboard::Code>(key - sf::Keyboard::A + IKeyboard::Code::kCodeA);

	else if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9)
		return static_cast<IKeyboard::Code>(key - sf::Keyboard::Num0 + IKeyboard::Code::kCode0);

	else if (key == sf::Keyboard::Escape)
		return IKeyboard::Code::kCodeEscape;

	else if (key == sf::Keyboard::Return)
		return IKeyboard::Code::kCodeEnter;

	else if (key == sf::Keyboard::Right)
		return IKeyboard::Code::kCodeRightArrow;

	else if (key == sf::Keyboard::Left)
		return IKeyboard::Code::kCodeLeftArrow;

	else if (key == sf::Keyboard::Up)
		return IKeyboard::Code::kCodeUpArrow;

	else if (key == sf::Keyboard::Down)
		return IKeyboard::Code::kCodeDownArrow;

	else if (key == sf::Keyboard::Space)
		return IKeyboard::Code::kCodeSpacebar;

	return IKeyboard::Code::kCodeMax;
}

IMouse::Button Engine::SFMLWindow::ConvertToButton(u32 button)
{
	if (button == sf::Mouse::Left)
		return IMouse::Button::kButtonLeft;

	if (button == sf::Mouse::Right)
		return IMouse::Button::kButtonRight;

	return IMouse::Button::kButtonNum;
}

bool Engine::SFMLWindow::ProcessEvents()
{
	sf::Event event;

	while (m_pSFMLWindow->pollEvent(event))
	{
		// Request for closing the window
		if (event.type == sf::Event::Closed)
		{
			m_pSFMLWindow->close();
			return false;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			Engine::IKeyboard::Code code = ConvertToCode(event.key.code);
			m_pKeyboard->SetKeyState(code, true); //if is keydown true, keyup false
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			Engine::IKeyboard::Code code = ConvertToCode(event.key.code);
			m_pKeyboard->SetKeyState(code, false); //if is keydown true, keyup false
		}
	}
	
	// Activate the window for OpenGL rendering
	m_pSFMLWindow->setActive();
	return true;
}

void * Engine::SFMLWindow::GetNativeWindow() const
{
	return m_pSFMLWindow.get();
}
#endif