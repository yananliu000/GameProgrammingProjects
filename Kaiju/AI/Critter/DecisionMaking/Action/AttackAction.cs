using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AttackAction : Action
{
    public AttackAction(ActionDefinition actionDefinition, AiBrain patron) : base(actionDefinition, patron)
    {
    }

    protected override void End()
    {
        if(m_target == null)
        {
            return;
        }

        m_patron.Context.m_aiManager.GiveACoinBack();

        //causing damange toward the player
        ShootableObject obj = m_target.GetComponent<ShootableObject>();

        if (obj)
        {
            obj.Hp--; //Todo: damage should be calculated
        }
        else
        {
#if DEBUG
            Debug.LogError("fail to get ShootableObject component.");
#endif
        }
    }

    public override bool Begin()
    {
        //play attack animation
        if(m_patron.Context.m_aiManager.GetACoin())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
