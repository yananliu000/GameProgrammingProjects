using System.Collections;
using System.Collections.Generic;
using UnityEngine;

 public sealed class AIManager: MonoBehaviour
{
    [SerializeField] int m_maxCoins = 5;
    int m_coins = 5;

    private void Reset()
    {
        m_coins = m_maxCoins;
    }

    private void Start()
    {
        Reset();    
    }

    public bool GetACoin()
    {
        if(m_coins > 0)
        {
            m_coins--;
            return true;
        }
        return false;
    }

    public void GiveACoinBack()
    {
        m_coins++;
    }
}