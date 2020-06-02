using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActionTargetPair 
{
    public AiTarget m_aiTarget = null;
    public ActionDefinition m_actionDef;
    public List<DecisionFactor> m_decisionFactors = new List<DecisionFactor>();

    public ActionTargetPair(AiTarget aiTarget, ActionDefinition actionDef)
    {
        m_aiTarget = aiTarget;
        m_actionDef = actionDef;

        if(m_aiTarget == null)
        {
            Debug.LogError("fail to get ai target");
            return;
        }

        //# decisionFactors = union of target.decisionFactors and actionDef.decisionFactors
        for (int i = 0; i < m_aiTarget.DecisionFactorArray.Count; i++)
        {
            for (int j = 0; j < this.m_actionDef.m_decisionFactors.Count; j++)
            {
                if (m_aiTarget.DecisionFactorArray[i] == this.m_actionDef.m_decisionFactors[j])
                {
                    m_decisionFactors.Add(m_aiTarget.DecisionFactorArray[i]);
                }

            }
        }
    }
}
