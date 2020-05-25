using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//# holds all action definitions
public sealed class AiActionManager : SingletonMonoBehavior<AiActionManager>
{
    #region ActionDatabse
    List<ActionDefinition> m_actionDefinitions;
    #endregion

    public static List<DecisionFactor> s_decisionsFactors = new List<DecisionFactor>();

    [Tooltip("Designer tuning area for decision factors ")]
    [SerializeField] private List<DecisionFactor> m_decisionFactors = new List<DecisionFactor>();
    private void Awake()
    {
        m_actionDefinitions = CreateActionDefinitionList.GenerateActionDefinitionListFromXML();

#if DEBUG
        if(m_actionDefinitions == null)
        {
            Debug.LogError("fail to load action definitions from xml", this.gameObject);
        }
#endif
        s_decisionsFactors = m_decisionFactors;
    }

    public static DecisionFactor FindDecisionFactorByType(StatBase.EStatType type)
    {
        //in optimal cases, the index of action definition should equal to (int) the enum type 
        int defaultIndex = (int)type;
        if (defaultIndex >= 0 && defaultIndex < s_decisionsFactors.Count)
        {
            DecisionFactor defaultDecisionFactor = s_decisionsFactors[defaultIndex];
            if (defaultDecisionFactor.m_type == type)
            {
                return defaultDecisionFactor;
            }
        }

        //if not, loop the list to find it and debug warning
        foreach (var decisionFactor in s_decisionsFactors)
        {
            if (decisionFactor.m_type == type)
            {
                return decisionFactor;
            }
        }
#if DEBUG
        Debug.LogError("The decision factor type is undefined", Instance.gameObject);
#endif
        return null;
    }

    public ActionDefinition FindActionDefinitionByType(ActionDefinition.EActionType type)
    {
        //in optimal cases, the index of action definition should equal to (int) the enum type 
        int defaultIndex = (int)type;
        if(defaultIndex >= 0 && defaultIndex < m_actionDefinitions.Count)
        {
            ActionDefinition defaultActionDefi = m_actionDefinitions[(int)type];
            if (defaultActionDefi.m_type == type)
            {
                return defaultActionDefi;
            }
        }
        //if not, loop the list to find it and debug warning
        foreach (var actionDefi in m_actionDefinitions)
        {
            if (actionDefi.m_type == type)
            {
#if DEBUG
                Debug.LogWarning("The order of the action definition list is not the optimal.", this.gameObject);
#endif
                return actionDefi;
            }
        }

#if DEBUG
        Debug.LogError("The action definition type is undefined", this.gameObject);
#endif
        return null;
    }

    private void Reset()
    {
        //decision factors list
        m_decisionFactors = new List<DecisionFactor>();

        for (int i = 0; i < (int)StatBase.EStatType.kStatsNum; i++)
        {
            m_decisionFactors.Add(new DecisionFactor((StatBase.EStatType)i));
        }

        s_decisionsFactors = m_decisionFactors;
    }
}
