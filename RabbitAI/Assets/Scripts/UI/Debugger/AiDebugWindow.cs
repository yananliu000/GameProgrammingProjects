using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AiDebugWindow: MonoBehaviour
{
    [Tooltip("The selected agent in debug mode")]
    [SerializeField] private AiBrain m_agent;

    [SerializeField] List<Slider> m_statSliders = new List<Slider>();
    
    [SerializeField] Text m_actionText;

    private void Update()
    {
        if (m_agent)
        {
            foreach (var item in m_statSliders)
            {
                StatTypeHolder statType = item.GetComponent<StatTypeHolder>();
                if (statType)
                {
                    item.value = Agent.GetComponent<StatManager>().FindStatByType(statType.m_type).Value;
                }
                else
                {

#if DEBUG
                    Debug.LogError("The slider needs a statSlider component", this.gameObject);

#endif
                }
            }

            SetText(m_agent);
        }
    }

    public AiBrain Agent
    {
        get => m_agent;
        set
        {
            if (value)
            {
                m_agent = value;
                foreach (var item in m_statSliders)
                {
                    StatTypeHolder statType = item.GetComponent<StatTypeHolder>();
                    item.onValueChanged.AddListener(delegate { m_agent.GetComponent<StatManager>().FindStatByType(statType.m_type).Value = item.value; });
                }
            }
        }
    }

    public void SetText(AiBrain agent)
    {
        Action action = agent.CurrentAction;
        m_actionText.text = $"Current Action : {action.ActionDefinition.m_type}\nTarget: {action.Target}\nPercentage: {(int)(action.elapsedTime / action.ActionDefinition.m_duration * 100)}\nCurrentState: {action.State}";
    }

}