using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Action
{
    //the time the action has taken
    protected float m_elapsedTime = 0;

    //the place the patron visited
    protected AiTarget m_target;

    //the action definition reference
    protected ActionDefinition m_actionDefinition;

    protected AiBrain m_patron;

    public AiTarget Target
    {
        get => m_target;
        set => m_target = value;
    }

    public Action(ActionDefinition actionDefinition, AiBrain patron)
    {
        m_actionDefinition = actionDefinition;
        m_elapsedTime = 0;
        m_patron = patron;
    }

    public virtual void Init(AiTarget target)
    {
        m_target = target;
    }

    public bool Update(float dt) 
    {
        if (m_elapsedTime == 0)
        {
            if(!this.Begin())
            {
                return true; //if Begin() return false, return true finish or cancel the action.
            }
        }

        m_elapsedTime += dt;

        if (m_elapsedTime > m_actionDefinition.m_duration)
        {
            this.End();
            return true;
        }
        else
        {
            m_elapsedTime += dt;
            return false;
        }
    }

    protected virtual void End() {}
    public virtual bool Begin() { return true; }
}
