using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyGameManager : MonoBehaviour
{
    private void Awake()
    {
        //seed rng
        uint seed = (uint)Random.Range(1, uint.MaxValue);
        XorshiftRNG.Instance.Seed = seed;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
