using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// # Returns a normalized value from 0 - 1
[System.Serializable]
public class DecisionFactor
{
    [Tooltip("The type of the decision factor")]
    public StatBase.EStatType m_type;

    [Tooltip("How the decision factor influence the utility")]
    [SerializeField] private AnimationCurve m_curve = null;

    [Tooltip("The comparable max value")]
    [SerializeField] private float m_maxValue = 100;

    public AnimationCurve Curve { get; }
    
    public DecisionFactor(StatBase.EStatType type)
    {
        m_type = type;
    }

    public virtual float Score(ActionTargetPair actionTargetPair, Context context)
    {
        if(m_curve != null)
        {
            float value = 0;
            StatManager statManager = context.m_agent.GetComponent<StatManager>();

            if(m_type == StatBase.EStatType.kDistance)
            {
                value = (actionTargetPair.m_aiTarget.transform.position - context.m_agent.transform.position).magnitude;
            }
            else
            {
                value = statManager.FindStatByType(m_type).Value;
            }

            float normalizedValue = Mathf.Clamp(value / m_maxValue, 0, 1);
            float result = m_curve.Evaluate(normalizedValue);
            return result;
        }
        else
        {
#if DEBUG
            Debug.LogError("The decision factor does not have a curve.");
#endif
        }
        return 0;

    }
}
