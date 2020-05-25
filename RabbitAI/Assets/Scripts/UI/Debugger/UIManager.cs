using System.Collections;
using System.Collections.Generic;
using UnityEngine;

#if DEBUG
public class UIManager : SingletonMonoBehavior<UIManager>
{
    [SerializeField] private GameObject m_canvas = null;

    #region Pick
    [Tooltip("Turn on/off pick")]
    [SerializeField] private bool m_isPick = false;

    [Tooltip("circle shown under the selected agent")]
    [SerializeField] private string m_pickCircleAddress = "Prefabs/PickCircle";

    [Tooltip("the selected agent")]
    [SerializeField] private GameObject m_pickAgent = null;

    [Tooltip("The tag of agents")]
    [SerializeField] private string m_agentTag = "Agent";

    private GameObject m_pickCircle = null;
    #endregion

    #region DEBUG
    [Tooltip("Turn on/off debug")]
    [SerializeField] private bool m_isDebuggerOn = false;

#if DEBUG
    [Tooltip("the adress for debugging window")]
    [SerializeField] private string m_debugWindowAddress = "Prefabs/DebugWindow";
    private AiDebugWindow m_debugWindow = null;
#endif
    #endregion

    GameObject PickAgent
    {
        set
        {
            if (value == null || value == m_pickAgent)
            {
                m_pickAgent = null;
                TurnSelectCanvas(false);
            }
            else
            {
                m_pickAgent = value;
                TurnSelectCanvas(true);
            }
        }
    }

#if DEBUG
    bool IsDebuggerOn
    {
        set
        {
            PickAgent = null;
            m_isDebuggerOn = value;
        }
    }
#endif

    bool Initialize()
    {
        //setting up debug
#if DEBUG
        m_debugWindow = (Instantiate(Resources.Load(m_debugWindowAddress), m_canvas.transform) as GameObject).GetComponent<AiDebugWindow>();
        if(m_debugWindow == null)
        {
            return false;
        }
        m_debugWindow.gameObject.SetActive(m_isDebuggerOn);
#endif
        //setting up picking
        m_isPick = false;
        m_pickCircle = Instantiate(Resources.Load(m_pickCircleAddress), transform) as GameObject;
        if(m_pickCircle == null)
        {
            return false;
        }
        m_pickCircle.SetActive(m_isPick);
        return true;
    }
    private void Start()
    {
        m_pickAgent = null;
        if(!Initialize())
        {
#if DEBUG
            Debug.LogError("Initialize failed", this.gameObject);
#endif
        }
    }
    private void UpdateInput()
    {
        if (Input.GetMouseButtonDown(0))
        {
            //get agent
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if (Physics.Raycast(ray, out hit))
            {
                if (hit.collider.CompareTag(m_agentTag))
                {
                    PickAgent = hit.collider.gameObject;
                }
            }
        }
    }

    void UpdateSelectedCircle()
    {
        if (m_pickAgent != null)
        {
            m_pickCircle.transform.position = m_pickAgent.transform.position;
        }
    }
    private void Update()
    {
        UpdateInput();
        UpdateSelectedCircle();
    }

    void TurnSelectCanvas(bool isOn)
    {
        if(m_isDebuggerOn)
        {
#if DEBUG
            m_debugWindow.gameObject.SetActive(isOn);
            m_pickCircle.SetActive(isOn);
            if(m_pickAgent)
            {
                m_debugWindow.Agent = m_pickAgent.GetComponent<AiBrain>();
            }
#endif
        }
        else
        {

        }
    }

    private void OnGUI()
    {
        GUI.BeginGroup(new Rect(0, 0, 150, 1000));

        //debug mode
        if(m_isDebuggerOn)
        {
#if DEBUG
            if (GUILayout.Button("Turn off Debugger", GUILayout.Width(150)))
            {
                IsDebuggerOn = false;
            }
            else if (GUILayout.Button("Add Instance", GUILayout.Width(150)))
            {
                PopulationManager.Instance.SpawnRandomAgent();
            }
            else if (GUILayout.Button("Destory Instance", GUILayout.Width(150)))
            {
                PopulationManager.Instance.DestroyAgent();
            }
#endif
        }
        //debug off
        else
        {
#if DEBUG
            if (GUILayout.Button("Turn on Debugger", GUILayout.Width(150)))
            {
                IsDebuggerOn = true;
            }
#endif
        }
        GUI.EndGroup();
    }
}
#endif