#include <assert.h>     /* assert */
#include "../Graphic/IGraphic.h"

#include "IMouse.h"
using Engine::IMouse;

bool IMouse::Init(Engine::IGraphic* graphicReference)
{
	for (int i = 0; i < Button::kButtonNum; ++i)
	{
		m_buttonState[i] = State::kUp;
	}
	m_graphicReference = graphicReference;
	return true;
}

void IMouse::SetButtonState(Button button, bool isDown)
{
	//assert only works for debug mode
	assert(button >= 0 && button < Button::kButtonNum);

	//press
	if (isDown && m_buttonState[button] != State::kDown)
	{
		m_buttonState[button] = State::kPress;
	}
	//release
	else if (!isDown && m_buttonState[button] != State::kUp)
	{
		m_buttonState[button] = State::kRelease;
	}
}

bool IMouse::IsButtonPressed(Button button)
{
	assert(button >= 0 && button < Button::kButtonNum);
	return m_buttonState[button] == State::kPress;
}

bool IMouse::IsButtonDown(Button button)
{
	assert(button >= 0 && button < Button::kButtonNum);
	return m_buttonState[button] == State::kPress || State::kDown;
}

void IMouse::NextFrame()
{
	//change release to up
	//change press to down
	for (int i = 0; i < Button::kButtonNum; ++i)
	{
		if (m_buttonState[i] == State::kPress)
		{
			m_buttonState[i] = State::kDown;
		}
		else if (m_buttonState[i] == State::kRelease)
		{
			m_buttonState[i] = State::kUp;
		}
	}

	//update mouse position 
}

V2f Engine::IMouse::GetMousePosition()
{
	return m_graphicReference->GetMousePosition();
}
