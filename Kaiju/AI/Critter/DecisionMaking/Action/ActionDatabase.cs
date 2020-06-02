using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//# holds all action definitions
public sealed class ActionDatabase : MonoBehaviour
{
    public static List<ActionDefinition> s_actionsDatabase = new List<ActionDefinition>();
    public static List<DecisionFactor> s_decisionsDatabase = new List<DecisionFactor>();

    [Tooltip("Designer tuning area")]

    [SerializeField] private List<ActionDefinition> m_actionsDatabase = new List<ActionDefinition>();

    private void Awake()
    {
        s_actionsDatabase = m_actionsDatabase;

        s_decisionsDatabase.Add(new DistanceDecisionFactor()); //  distance 0 
        s_decisionsDatabase.Add(new TargetHealthDecisionFactor()); //  targethealth 1

        FindActionDefinitionByType(ActionDefinition.EActionType.kAttack).m_decisionFactors = new List<DecisionFactor> { s_decisionsDatabase[0], s_decisionsDatabase[1] };
        
        ObjectManager objManager = FindObjectOfType<ObjectManager>();
    }

    public static DecisionFactor FindDecisionFactorByType(DecisionFactor.EDecisionFactorType type)
    {
        switch (type)
        {
            //for now
            case DecisionFactor.EDecisionFactorType.kDistance:
                return s_decisionsDatabase[0];
            case DecisionFactor.EDecisionFactorType.kTargetHealth:
                return s_decisionsDatabase[1];
            default:
#if DEBUG
                Debug.LogError("fail to get the decision factor by type");
#endif
                return null;
        }
    }

    public static ActionDefinition FindActionDefinitionByType(ActionDefinition.EActionType type)
    {
        foreach (var actionDefi in s_actionsDatabase)
        {
            if(actionDefi.m_type == type)
            {
                return actionDefi;
            }
        }
        return null;
    }
}
