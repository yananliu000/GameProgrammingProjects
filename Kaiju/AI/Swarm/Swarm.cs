using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Culham Otton + Yanan Liu
/// Swarms of critters
/// The idea was to keep the swarm a low cost as possible to allow more in the level at one time.
/// LOD system aids in this.
/// </summary>
public class Swarm : MonoBehaviour
{
    [SerializeField] private float mWalkSpeed = .05f;
    [SerializeField] private float m_randomRotateRange = 0.2f;
    private float m_breakingUpInterval = 0.2f;
    private float m_breakingUpAccelerationSpeed = 2;

    //State 3 == far // State 2 == Mid // State 1 == Near
    enum ESwarmState
    {
        kNear = 1,
        kMid,
        kFar,
        kBreakingUp
    }

    [SerializeField] ESwarmState m_state = ESwarmState.kFar;
    // All critters in swarm
    [SerializeField] GameObject[] m_crittersInSwarm = new GameObject[10];
    // The axis spin while having critters childed to them to imitate the movement of a swarm as simply as possible
    [SerializeField] GameObject[] m_axis = new GameObject[3];

    // Determines which critter dies in far LOD
    int m_critterDying = 0;
    [SerializeField] int m_critterDiesInHits;
  
    // In Far LOD a random critter dies when a random number of player projectiles hits the swarm collider 
    // once one dies a rather number of hits till next death is determined
    int m_critterDiesInHitsMin = 1;
    int m_critterDiesInHitsMax = 5;

    float m_critterUpSpeed = .5f;
    float m_critterForwardSpeed = .5f;
    float m_critterLeftSpeed = .5f;

    // Starting rotation speeds for axis
    Vector3 m_axiOneRot = new Vector3(1.5f, 2f, 1.5f);
    Vector3 m_axiTwoRot = new Vector3(-1.5f, -1.5f, -2f);
    Vector3 m_axiThreeRot = new Vector3(-1.5f, 2f, 1.5f);

    void Start()
    {
        //Sets random health till first critter dies
        m_critterDiesInHits = Random.Range(m_critterDiesInHitsMin, m_critterDiesInHitsMax + 1); 

        //Randomizes Starting Axis
        foreach (var axis in m_axis)
        {
            axis.transform.eulerAngles = new Vector3(Random.Range(0f, 360f), Random.Range(0f, 360f), Random.Range(0f, 360f));
        }
    }

    /// <summary>
    /// Moves forward and spins axis
    /// </summary>
    void Update()
    {
        AxiRotation();

        //move
        transform.Translate(0, 0, mWalkSpeed);
    }

    /// <summary>
    /// Critters Unparent from the swarm and the swarm body along with dead critters are destroyed
    /// </summary>
    /// <returns></returns>
    IEnumerator BreakingUPFromSwarm()
    {
        float breakingUpInterval = m_breakingUpInterval;

        for (int i = 0; i < m_crittersInSwarm.Length; i++)
        {
            breakingUpInterval = m_breakingUpInterval / m_breakingUpAccelerationSpeed; 

            if (m_crittersInSwarm[i].activeSelf == true)
            {
                yield return new WaitForSeconds(breakingUpInterval);
                m_crittersInSwarm[i].transform.parent = null;
                Critter critter = m_crittersInSwarm[i].GetComponent<Critter>();
                critter.enabled = true;
                critter.Initialize();
            }
        }
        Destroy(gameObject);
    }


    /// <summary>
    /// Kills of the next critter in the array
    /// Gets ready to kill the next
    /// Resets the hits required to kill the next Critter
    /// </summary>
    /// <param name="hit"></param>
    public void Hit(GameObject hit)
    {
        switch (m_state)
        {
            case ESwarmState.kNear:
                break;
            case ESwarmState.kMid:
                hit.SetActive(false);
                break;
            case ESwarmState.kFar:
                m_critterDiesInHits--;
                if (m_critterDiesInHits <= 0)
                {
                    m_crittersInSwarm[m_critterDying].SetActive(false);
                    m_critterDying++;
                    m_critterDiesInHits = Random.Range(m_critterDiesInHitsMin, m_critterDiesInHitsMax + 1);
                }
                break;
            default:
                break;
        }
        
        //check alive: if one small critter is alive, the group is alive
        foreach(var critter in m_crittersInSwarm)
        {
            if(critter.activeSelf == true)
            {
                return;
            }
        }

        //no one is alive, destory the group 
        Destroy(gameObject);
    }


    /// <summary>
    /// Constantly Rotates Axis to make the swarm look animated
    /// </summary>
    void AxiRotation()
    {
        foreach (var item in m_axis)
        {
            item.transform.Rotate(new Vector3(Mathf.Clamp((m_axiOneRot.x + Random.Range(-m_randomRotateRange, m_randomRotateRange)), -2, 2), Mathf.Clamp((m_axiOneRot.y + Random.Range(-m_randomRotateRange, m_randomRotateRange)), -2, 2), Mathf.Clamp((m_axiOneRot.z + Random.Range(-m_randomRotateRange, m_randomRotateRange)), -2, 2)));
        }

        for (int i = 0; i < m_crittersInSwarm.Length; i++)
        {
            if (m_crittersInSwarm[i] != null && m_crittersInSwarm[i].activeSelf == true)
            {
                m_crittersInSwarm[i].transform.rotation = this.transform.rotation;
            }
        }
    }

    /// <summary>
    /// Toggles the Swarm's colliders from being the large overall for long range to the smaller colliders on each Critter
    /// </summary>
    void SetMidState()
    {
        m_state = ESwarmState.kMid;

        gameObject.GetComponent<SphereCollider>().enabled = false;

        foreach (var critter in m_crittersInSwarm)
        {
            critter.GetComponent<SphereCollider>().enabled = true;
        }
    }

    /// <summary>
    /// Checks for LOD planes
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "sMid" && m_state == ESwarmState.kFar)
        {
            SetMidState();
        }
        else if (other.gameObject.tag == "sNear" && m_state == ESwarmState.kMid)
        {
            m_state = ESwarmState.kBreakingUp;
            StartCoroutine(BreakingUPFromSwarm());
        }
    }
}
