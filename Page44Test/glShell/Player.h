#pragma once
#include "MyVector2.h"
class Player
{
private:
    /* Here will be the instance stored. */
    static Player* m_pInstance;
    float m_speedFactor;

    /* Private constructor to prevent instancing. */
    Player();

public:
    MyVector2 m_playerPos;
    MyVector2 m_playerSpeed;
    int m_coinNum;
    int m_lives;

    /* Static access method. */
    static Player* GetInstance();
    void Start();
    void Update(float dt);
};

