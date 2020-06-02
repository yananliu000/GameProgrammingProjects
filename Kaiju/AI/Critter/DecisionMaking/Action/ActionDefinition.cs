using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class ActionDefinition 
{
    public enum EActionType
    {
        kAttack,
    }
    
    public EActionType m_type;
    public float m_duration;
    [SerializeField] private float m_durationRandRange = 0.5f;

    //decisionFactors 
    public List<DecisionFactor> m_decisionFactors;

    public Action CreateAction(AiBrain patron, AiTarget target)
    {
        Action newAction;
        switch (m_type)
        {
            case EActionType.kAttack:
                newAction = new AttackAction(this, patron);
                break;
            default:
                newAction = null;
                Debug.Log("Undefnied action type");
                break;
        }
        newAction.Init(target);
        return newAction;
    }
}
