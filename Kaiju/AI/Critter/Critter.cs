using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Land
//Run the decision making => move to the player then attack 

/// <summary>
/// Culham Otton, Yanan Liu
/// AI script controls the behavior of an individual scritter by using a simple state machine. 
/// </summary>
public class Critter : MonoBehaviour
{
    [Tooltip("How fast does the critter move")]
    private float m_walkSpeed = .001f;

    [Tooltip("Randomization of flying in landing")]
    [SerializeField] float m_landSpeedRandomRange = 2f;

    [Tooltip("Randomization of rotating in landing")]
    [SerializeField] float m_rotateSpeedRandomRange = 0.2f;

    [Tooltip("How fast does the critter land")]
    private float m_landSpeed = 5f;

    [Tooltip("How fast does the critter rotate")]
    private float m_rotateSpeed = 0.8f;

    [SerializeField] private float m_arriveDistance = 0.25f;
    [SerializeField] private float m_defaultDashTimer = .25f;
    [SerializeField] private float m_dashTimer = .25f;

    //LOD Bodies
    [SerializeField] GameObject m_LowPolyBody;
    [SerializeField] GameObject m_HighPolyBody;

    private AiBrain m_aiBrain;

    //landing
    //[SerializeField] string m_landableSurfaceTag = "Landable";
    private Quaternion m_targetRotation = Quaternion.Euler(0, 0, -90);
    [SerializeField] private float m_randomRotateRange = 0.2f;

    enum ECritterState
    {
        kFlying, //Fly toward the player
        kLanding, //Fly toward the landable surface
        kLanded, //Shoot the player
    }

    private Vector3 m_landingTarget = Vector3.zero;
    [SerializeField] ECritterState m_state = ECritterState.kFlying;

    /// <summary>
    /// Called when breaking up from the swarm 
    /// </summary>
    public void Initialize()
    {
        m_LowPolyBody.SetActive(false);
        m_HighPolyBody.SetActive(true);
        m_landSpeed += Random.Range(-m_landSpeedRandomRange, m_landSpeedRandomRange);
        m_rotateSpeed += Random.Range(-m_rotateSpeedRandomRange, m_rotateSpeedRandomRange);
        m_aiBrain = GetComponent<AiBrain>();
        m_aiBrain.enabled = true;
        GetComponent<SphereCollider>().radius = 1.07f;
#if DEBUG
        if (m_aiBrain == null)
        {
            Debug.LogError("Fail to get AiBrain");
        }
#endif
    }

    /// <summary>
    /// States Update 
    /// </summary>
    void Update()
    {
        switch (m_state)
        {
            case ECritterState.kFlying:
                //try to find a landable surface, otherwise flying forward
                if(IsAnyLandableSurface())
                {
                    m_state = ECritterState.kLanding;
                }
                else
                {
                    Move();
                }
                break;

            case ECritterState.kLanding:
                //fly toward the surface
                if (MyMath.InRange(transform.position, m_landingTarget, m_arriveDistance))
                {
                    m_state = ECritterState.kLanded;
                }
                else
                {
                    MoveToTarget(m_landingTarget);
                }
                break;

            case ECritterState.kLanded:
                //attack the player 
                if (m_aiBrain.m_currentAction == null)
                {
                    m_aiBrain.MakeDecision();
                }

                break;

            default:
                break;
        }
    }

    /// <summary>
    /// Walk forward 
    /// </summary>
    void Move()
    {
        m_dashTimer -= Time.deltaTime;
        transform.Translate(0, 0, m_walkSpeed);
        if (m_dashTimer <= 0)
        {
            m_walkSpeed = -m_walkSpeed;
            m_dashTimer = m_defaultDashTimer;
        }
    }

    /// <summary>
    /// Move toward the target
    /// </summary>
    /// <param name="target"></param>
    void MoveToTarget(Vector3 target)
    {
        // The step size is equal to speed times frame time.
        float moveStep = m_landSpeed * Time.deltaTime;

        // Move towards the target direction by one step
        transform.position = Vector3.MoveTowards(transform.position, target, moveStep);
    }

    /// <summary>
    /// Update rotation for landing 
    /// </summary>
    private void LateUpdate()
    {
        if (m_state == ECritterState.kLanded)
        {
            transform.rotation = Quaternion.Slerp(transform.rotation, m_targetRotation, Time.deltaTime * m_rotateSpeed);
        }
        else
        {
           transform.Rotate(new Vector3(Random.Range(-m_randomRotateRange, m_randomRotateRange)
               , Random.Range(-m_randomRotateRange, m_randomRotateRange)
               , Random.Range(-m_randomRotateRange, m_randomRotateRange)));
        }
    }

    /// <summary>
    /// The response of being hit
    /// </summary>
    public void Hit()
    {
        Destroy(gameObject);
    }

    /// <summary>
    /// find any landable surface
    /// </summary>
    /// <returns></returns>
    bool IsAnyLandableSurface()
    {
        LandingController landingController = FindObjectOfType<LandingControllerManager>().GetLandingController(transform.position);
        if(landingController)
        {
            LandingController.LandResult result = landingController.GetLandableSurface();
            m_landingTarget = result.m_landingPoint;
            m_targetRotation = result.m_landingAngle;
            return true;
        }
        return false;
    }
}
