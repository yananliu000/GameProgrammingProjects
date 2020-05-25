using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public sealed class Action
{
    public enum EActionState
    {
        kBeforeStart,
        kOnStart,
        kOnProcessing,
        kOnEnd,
        kFinished,
        kUninitialized,
    }

    [SerializeField] private EActionState m_state = EActionState.kUninitialized;

    //the time the action has taken
    [SerializeField] protected float m_elapsedTime = 0;

    //the place the patron visited
    protected AiTarget m_target = null;

    //the action definition reference
    protected ActionDefinition m_actionDefinition = null;

    protected AiBrain m_agent = null;

    public ActionDefinition ActionDefinition { get => m_actionDefinition; }
    public EActionState State { get => m_state; }
    public float elapsedTime { get=> m_elapsedTime; }


    public AiTarget Target
    {
        get => m_target;
        set => m_target = value;
    }

    public Action(ActionDefinition actionDefinition, AiBrain patron, AiTarget target)
    {
        m_state = EActionState.kBeforeStart;
        m_actionDefinition = actionDefinition;
        m_elapsedTime = 0;
        m_agent = patron;
        m_target = target;
    }

    public bool Update(float dt) 
    {
        if (m_elapsedTime == 0)
        {
            //begin
            m_state = EActionState.kOnStart;
            foreach (var item in m_actionDefinition.m_beginActionNodes)
            {
                item.Execute(m_agent);
            }
            m_state = EActionState.kOnProcessing;
        }

        if (m_elapsedTime > m_actionDefinition.m_duration)
        {
            //end
            m_state = EActionState.kOnEnd;
            foreach (var item in m_actionDefinition.m_endActionNodes)
            {
                item.Execute(m_agent);
            }
            m_state = EActionState.kFinished;
            return true;
        }
        else
        {
            m_elapsedTime += dt;
            return false;
        }
    }
}
