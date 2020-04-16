#pragma once
class GameManager
{
private:
    /* Here will be the instance stored. */
    static GameManager* m_pInstance;

    /* Private constructor to prevent instancing. */
    GameManager() :m_matchTimer(3)
        ,m_waitingTime(0)
    {

    }

    //watch for a few seconds to begin another game after one's finished
    const float m_matchTimer;

    float m_waitingTime;

public:
    /* Static access method. */
    static GameManager* GetInstance();

    bool Update(float dt) 
    {
        m_waitingTime -= dt;

        if (m_waitingTime > 0)
        {
            return false;
        }
        return true;
    }

    void StartTimer()
    {
        m_waitingTime = m_matchTimer;
    }

    bool isTimerFinished()
    {
        return m_waitingTime <= 0;
    }
};

