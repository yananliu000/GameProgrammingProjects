using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// The manager that owns all the landing controllers and assign to the requested agent a landable position from the closest controller.
/// </summary>
public class LandingControllerManager : MonoBehaviour
{
    [SerializeField] private List<LandingController> m_landingControllerList;

    private void Start()
    {
        m_landingControllerList = new List<LandingController>();
        m_landingControllerList.AddRange(GetComponentsInChildren<LandingController>());
    }

    /// <summary>
    /// Assign the agent a closest controller based on the agent's location.
    /// </summary>
    /// <param name="location"></param>
    /// <returns></returns>
    public LandingController GetLandingController(Vector3 location)
    {
        LandingController controller = m_landingControllerList[0];
        float minValue = GetHeuristicDistance(m_landingControllerList[0].transform.position, location);
        for (int i = 1; i < m_landingControllerList.Count; i++)
        {
            float value = GetHeuristicDistance(m_landingControllerList[i].transform.position, location);
            if (value < minValue)
            {
                minValue = value;
                controller = m_landingControllerList[i];
            }
        }
        return controller;
    }

    /// <summary>
    /// Get heuristic distance between two positions 
    /// </summary>
    /// <param name="self"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    float GetHeuristicDistance(Vector3 self, Vector3 target)
    {
        return Mathf.Abs(self.x - target.x) + Mathf.Abs(self.y - target.y) + Mathf.Abs(self.z - target.z);
    }
}
