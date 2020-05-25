using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public sealed class StatModifyNode : ActionNodeBase
{
    public StatBase.EStatType m_stateType;
    public float m_value;

    public StatModifyNode(StatBase.EStatType statType, float value)
    {
        m_stateType = statType;
        m_value = value;
        m_nodeType = ENodeType.kStatModify;
    }

    public sealed override bool Execute(AiBrain agent)
    {
        StatBase stat = agent.GetComponent<StatManager>().FindStatByType(m_stateType);
        stat.Value += m_value;

        if(stat == null)
        {
#if DEBUG
            Debug.LogError("Undefined modify type.");
#endif
            return false;

        }
        return true;
    }
}
