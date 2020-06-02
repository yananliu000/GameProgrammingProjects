using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AiTarget: MonoBehaviour
{
    //# float multiplied into the score
    public float baseDesire;

    //decisionFactors 
    protected List<DecisionFactor> m_decisionFactors = new List<DecisionFactor>();

    protected List<ActionDefinition> m_actionDefinitions = new List<ActionDefinition>();

    [SerializeField] protected List<ActionDefinition.EActionType> m_actionDefTypes = new List<ActionDefinition.EActionType>();
    [SerializeField] protected List<DecisionFactor.EDecisionFactorType> m_decisionFacTypes = new List<DecisionFactor.EDecisionFactorType>();

    protected void Start()
    {
        FindObjectOfType<ObjectManager>().AddIntoObjectList(this);
        LoadActionDefinitions();
    }

    public List<DecisionFactor> DecisionFactorArray
    {
        get => m_decisionFactors;
    }

    public List<ActionDefinition> ActionDefinitionArray
    {
        get => m_actionDefinitions;
    }
    public void LoadActionDefinitions()
    {
        foreach (var type in m_actionDefTypes)
        {
            m_actionDefinitions.Add(ActionDatabase.FindActionDefinitionByType(type));
        }

        foreach (var type in m_decisionFacTypes)
        {
            m_decisionFactors.Add(ActionDatabase.FindDecisionFactorByType(type));
        }
    }
}
