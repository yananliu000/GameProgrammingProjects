using System.Collections;
using System.Collections.Generic;
using UnityEngine;



[System.Serializable]
public class ActionDefinition
{
    public enum EActionType
    {
        kEat,
        kDrink,
        kSleep,
        kPlay,
        kBath,
        kPooPoo,
        kTalk,
        kActionTypeNum,
        kDefault
    }

    [Tooltip("The type of the action, used to identify the action in designer tunning areas for the action database and ai objects")]
    public EActionType m_type = EActionType.kDefault;

    [Tooltip("The time the action takes to finish")]
    public float m_duration = 2;

    [Tooltip("The action nodes to execute when the action begins")]
    public List<ActionNodeBase> m_beginActionNodes = new List<ActionNodeBase>();

    [Tooltip("The action nodes to execute when the action ends")]
    public List<ActionNodeBase> m_endActionNodes = new List<ActionNodeBase>();

    [Tooltip("The decision factors can influence the action")]
    public List<StatBase.EStatType> m_decisionFactorsType = new List<StatBase.EStatType>();
    
    public ActionDefinition(EActionType type, float duration)
    {
        m_type = type;
        m_duration = duration;
        m_beginActionNodes = new List<ActionNodeBase>();
        m_endActionNodes = new List<ActionNodeBase>();
        m_decisionFactorsType = new List<StatBase.EStatType>();
    }

    public ActionDefinition(EActionType type, float duration, List<ActionNodeBase> beginNodes, List<ActionNodeBase> endNodes, List<StatBase.EStatType> decisionFactors)
    {
        m_type = type;
        m_duration = duration;
        m_beginActionNodes = beginNodes;
        m_endActionNodes = endNodes;
        m_decisionFactorsType = decisionFactors;
    }

    public Action CreateAction(AiBrain patron, AiTarget target)
    {
        Action newAction = new Action(this, patron, target);
        return newAction;
    }
}
