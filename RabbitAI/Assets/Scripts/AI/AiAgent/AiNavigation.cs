using UnityEngine;
using UnityEngine.AI;
public class AiNavigation : MonoBehaviour
{
    [Tooltip("The destination of the agent")]
    [SerializeField] private Transform m_goal;

    [Tooltip("Is the agent arrived the destination")]
    [SerializeField] private bool m_isArrived = false;

    [Tooltip("How far away from the destination will agent will")]
    [SerializeField] private float m_stoppingDistance = 0.5f;

    [Tooltip("The state name in animator of Run state")]
    [SerializeField] private string m_runAnimationName = "Run";

    private NavMeshAgent m_navMeshAgent = null;

    private AiBrain m_aiAgent = null;

    private void Awake()
    {
        m_navMeshAgent = GetComponent<NavMeshAgent>();
        m_aiAgent = GetComponent<AiBrain>();
        m_isArrived = false;

#if DEBUG
        if (m_navMeshAgent == null)
        {
            Debug.LogError("Fail to get NavMeshAgent component", this.gameObject);
        }

        if (m_aiAgent == null)
        {
            Debug.LogError("Fail to get AiAgent component", this.gameObject);
        }
#endif
    }
    public bool IsArrived
    {
        get
        {
            if(m_isArrived == false)
            {
                if (m_navMeshAgent.remainingDistance <= m_navMeshAgent.stoppingDistance)
                {
                    m_isArrived = true;
                }
                if (m_navMeshAgent.isPathStale)
                {
                    m_navMeshAgent.ResetPath();
                }
            }
            return m_isArrived;
        }
    }

    public Transform Goal
    {
        set
        {
            if(value != null && m_navMeshAgent != null && m_navMeshAgent.isOnNavMesh)
            {
                //set new goal
                m_goal = value;

                m_navMeshAgent.destination = m_goal.position;

                //check did already arrives
                float distance = Vector3.Distance(m_navMeshAgent.destination, m_navMeshAgent.transform.position);
                if (distance > m_navMeshAgent.stoppingDistance)
                {
                    m_isArrived = false;

                    //set animator to run
                    m_aiAgent.GetComponent<Animator>().Play(m_runAnimationName);
                }
            }
        }
    }

    void Start()
    {
        m_navMeshAgent = GetComponent<NavMeshAgent>();
        if(! m_navMeshAgent)
        {
            Debug.LogError("fail to get NavMeshAgent component.", this.gameObject);
        }
        m_navMeshAgent.stoppingDistance = m_stoppingDistance;
    }
}
