using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class TargetHealthDecisionFactor : DecisionFactor
{
    public float m_maxMotive = 100;

    public override float Score(ActionTargetPair actionTargetPair, Context context)
    {
        if(actionTargetPair.m_aiTarget == null)
        {
            return 0;
        }
        ShootableObject obj = actionTargetPair.m_aiTarget.GetComponent<ShootableObject>();
        if(obj)
        {
            float value = obj.Hp;
            float normalizedDistance = value / m_maxMotive;
            float result = 1 - Mathf.Pow(Mathf.Clamp(normalizedDistance, 0, 1), 2);
            return result; //# curve
        }
        else
        {
#if DEBUG
            Debug.LogError("component ShootableObject not found");
#endif
            return 0;
        }
    }
}
