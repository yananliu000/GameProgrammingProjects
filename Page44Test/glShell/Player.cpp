#include "Player.h"
#include "Utility.h"

/* Null, because instance will be initialized on demand. */
Player* Player::m_pInstance = 0;

Player::Player()
    :m_speedFactor(0)
    , m_playerPos(0,0)
    , m_playerSpeed(0,0)
    , m_coinNum(0)
    , m_lives(0)
{
}

Player* Player::GetInstance()
{
    if (m_pInstance == 0)
    {
        m_pInstance = new Player();
    }

    return m_pInstance;
}

void Player::Start()
{
    m_playerPos.x = 0.0f;
    m_playerPos.y = 0.0f;
    m_speedFactor = 5;
    m_lives = 3;
    m_playerSpeed = { 1, 0 };
}

void Player::Update(float dt)
{
    //lose
    if (m_lives <= 0)
    {
        return;
    }

    //update 
    m_playerPos.x += m_speedFactor * m_playerSpeed.x * dt;
    m_playerPos.y += m_speedFactor * m_playerSpeed.y * dt;

    if (m_playerPos.x >= END_HOR_OFFSET) {
        m_playerPos.x = END_HOR_OFFSET;
        m_playerSpeed.x = -m_playerSpeed.x;
    }
    else if (m_playerPos.x <= START_HOR_OFFSET) {
        m_playerPos.x = START_HOR_OFFSET;
        m_playerSpeed.x = -m_playerSpeed.x;
    }
    if (m_playerPos.y >= END_VER_OFFSET) {
        m_playerPos.y = END_VER_OFFSET;
        m_playerSpeed.y = -m_playerSpeed.y;
    }
    else if (m_playerPos.y <= START_VER_OFFSET) {
        m_playerPos.y = START_VER_OFFSET;
        m_playerSpeed.y = -m_playerSpeed.y;
    }
}

