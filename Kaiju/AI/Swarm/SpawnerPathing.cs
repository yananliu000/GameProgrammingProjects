using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// Culham Otton
/// Holds spawner and waypoint pathing by holding each waypoints next possiblities
/// </summary>
public class SpawnerPathing : MonoBehaviour
{
    // List of possible next places for the swarm to go
    [SerializeField] public List<GameObject> PossibleNext = new List<GameObject>();

    /// <summary>
    /// If there is only one send the swarm there ELSE roll randomly to determine where to send it
    /// </summary>
    /// <returns></returns>
    public GameObject WhereToNext()
    {
        GameObject Next = null;

        if (PossibleNext.Count > 1)
        {
            int Which = Random.Range(0, PossibleNext.Count);
            Next = PossibleNext[Which];
        }
        else if (PossibleNext.Count == 1)
        {
            Next = PossibleNext[0];
        }

        return Next;
    }
}
