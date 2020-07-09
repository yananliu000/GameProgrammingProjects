#include <assert.h>

#include "IKeyboard.h"
using Engine::IKeyboard;

bool IKeyboard::Init()
{
	for (int i = 0; i < Code::kCodeMax; ++i)
		m_buttonState[i] = State::kUp;
	return true;
}

void IKeyboard::SetKeyState(Code code, bool isDown)
{
	assert(code >= 0 && code < Code::kCodeMax);

	//press
	if (isDown && m_buttonState[code] != State::kDown)
	{
		m_buttonState[code] = State::kPress;
	}
	//release
	else if (!isDown && m_buttonState[code] != State::kUp)
	{
		m_buttonState[code] = State::kRelease;
	}
}

bool IKeyboard::IsKeyPressed(Code code)
{
	assert(code >= 0 && code < Code::kCodeMax);
	return m_buttonState[code] == State::kPress;

}

bool IKeyboard::IsKeyDown(Code code)
{
	assert(code >= 0 && code < Code::kCodeMax);
	return m_buttonState[code] == State::kPress || m_buttonState[code] == State::kDown;
}

void IKeyboard::NextFrame()
{
	//change release to up
	//change press to down
	for (int i = 0; i < Code::kCodeMax; ++i)
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
}
