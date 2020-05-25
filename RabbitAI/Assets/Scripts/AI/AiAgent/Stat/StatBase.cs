using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class StatBase 
{
    public enum EStatType
    {
        kHunger,
        kEnergy,
        kFun,
        kThirsty,
        kSocial,
        kHygiene,
        kBladder,

        kStatsNum,
        kNone,

        kDistance,
    }

    public StatBase.EStatType m_type;

    [SerializeField] private float m_decayRate = 0.5f;
    [SerializeField] private float m_max = 100;
    [SerializeField] private float m_min = 0;
    [SerializeField] private float m_value = 80;
    [SerializeField] private float m_multiplier = 1;
 
    public StatBase(StatBase.EStatType type, float decayRate  = 0.5f, float max = 100, float min = 0, float value = 80, float multiplier = 1)
    {
        m_type = type;
        m_decayRate = decayRate;
        m_min = min;
        m_max = max;
        m_value = value;
        m_multiplier = multiplier;
    }

    public float Min { get => m_min; set => m_min = value; }
    public float Max { get => m_max; set => m_max = value; }

    public void Update(float deltaTime)
    {
        Value -= m_decayRate * m_multiplier * deltaTime;
    }

    public float Multiplier
    {
        set => m_multiplier = value;
    }

    public float DecayRate
    {
        set => m_decayRate = value;
    }
    public float Value
    {
        get => m_value;
        set
        {
            m_value = value;
            m_value = Mathf.Clamp(m_value, m_min, m_max);
        }
    }
}
