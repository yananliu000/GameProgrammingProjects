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

    [SerializeField] protected List<StatBase.EStatType> m_decisionFacTypes = new List<StatBase.EStatType>();

    bool m_isInitialized = false;

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
        m_isInitialized = true;
        foreach (var type in m_actionDefTypes)
        {
            m_actionDefinitions.Add(AiActionManager.Instance.FindActionDefinitionByType(type));
        }

        foreach (var type in m_decisionFacTypes)
        {
            m_decisionFactors.Add(AiActionManager.FindDecisionFactorByType(type));
        }
    }

    private void OnDestroy()
    {
        ObjectManager.Instance.RemoveFromObjectList(this);
    }

    private void Start()
    {
        ObjectManager.Instance.AddIntoObjectList(this);

        if(m_isInitialized == false)
        {
            LoadActionDefinitions();
        }
    }

    public override string ToString()
    {
        return gameObject.name;
    }
}
