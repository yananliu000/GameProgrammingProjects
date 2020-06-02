using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[System.Serializable]
public class DistanceDecisionFactor : DecisionFactor
{
    public float m_maxDistance = 100;

    public override float Score(ActionTargetPair actionTargetPair, Context context)
    {
        if (actionTargetPair.m_aiTarget != null)
        {
            Vector3 delta = actionTargetPair.m_aiTarget.transform.position - context.m_patron.transform.position;
            float normalizedDistance = delta.magnitude / m_maxDistance;
            return 1 - Mathf.Pow(Mathf.Clamp(normalizedDistance, 0, 1), 3); //# curve
        }
        return 0;
    }

}
