#include "GameManager.h"
GameManager* GameManager::m_pInstance = 0;

GameManager* GameManager::GetInstance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new GameManager();
    }

    return m_pInstance;
}