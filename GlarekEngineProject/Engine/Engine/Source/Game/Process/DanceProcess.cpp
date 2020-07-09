#include "DanceProcess.h"
#include "../Actor/Actor.h"

bool Engine::DanceProcess::Init()
{
	m_danceMove = EDanceMove::kInitialized;
	m_timer = 0;

	auto pOwner = m_pOwner.lock();

	if (!pOwner)
	{
		return false;
	}

	m_pTransformComponent = static_cast<TransformComponent*>(pOwner->GetComponent<TransformComponent>());

	if (!m_pTransformComponent)
	{
		return false;
	}

	return true;
}

void Engine::DanceProcess::Update(f32 deltaSeconds)
{
	if (m_pOwner.expired())
	{
		ChangeState(EState::kFailed);
		return;
	}

	if (m_danceMove == EDanceMove::kMoveNum)
	{
		//change sprite to blue 
		m_pOwner.lock()->GetComponent<SpriteRenderComponent>()->SetSrcRect({ 33, 98, 14, 14 });
		ChangeState(EState::kSucceeded);
	}
	else
	{
		//change direction, reset timer
		if (m_timer <= deltaSeconds)
		{
			m_speed = V2f(0.f, 0.f);
			m_danceMove = EDanceMove(m_danceMove + 1);
			m_timer = m_intervalTime;
			switch (m_danceMove)
			{
			case EDanceMove::kMoveLeft:
				m_speed.x = -velocity;
				break;

			case EDanceMove::kMoveRight:
				m_speed.x = velocity;
				break;

			case EDanceMove::kMoveUp:
				m_speed.y = -velocity;
				break;

			case EDanceMove::kMoveDown:
				m_speed.y = velocity;
				break;

			default:
				break;
			}
		}
		else
		{
			m_pTransformComponent->MoveToward(m_speed.x*deltaSeconds, m_speed.y*deltaSeconds);
			m_timer -= deltaSeconds;
		}
	}
}
