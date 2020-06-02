using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// Culham Otton
/// Controls what the swarm does when it hits a waypoint
/// </summary>
public class SwarmPathing : MonoBehaviour
{
    [SerializeField] GameObject WayPoint;
    
    /// <summary>
    /// Spawner will feed Waypoint
    /// </summary>
    /// <param name="NewWayPoint"></param>
    public void Initialize(GameObject NewWayPoint)
    {
        print(NewWayPoint.transform.position);
        gameObject.transform.LookAt(NewWayPoint.transform, Vector3.up);
    }

    /// <summary>
    /// When Swarm collides with waypoint it gets the next Waypoint and looks at it if it's a Death tag then destroy it.
    /// </summary>
    /// <param name="other"></param>
    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "WayPoint")
        {
            WayPoint = other.gameObject.GetComponent<SpawnerPathing>().WhereToNext();
            gameObject.transform.LookAt(WayPoint.transform);
        }
        else if(other.gameObject.tag == "Death")
        {
            Destroy(gameObject);
        }
    }
}
