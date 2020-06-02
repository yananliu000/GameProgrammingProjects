using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// # Returns a normalized value from 0 - 1
[System.Serializable]
public abstract class DecisionFactor
{
    public enum EDecisionFactorType
    {
        kDistance,
        kTargetHealth,
    }

    public abstract float Score(ActionTargetPair actionTargetPair, Context context);
}
