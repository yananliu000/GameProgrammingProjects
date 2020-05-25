using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopulationManager : SingletonMonoBehavior<PopulationManager>
{
    [Tooltip("The interval time")]
    [SerializeField] private float m_timer = 2;

    [Tooltip("The passed time")]
    [SerializeField] private float m_elapsedTime = 0;

    [Tooltip("Close after nth customer")]
    [SerializeField] private int m_closeCount = 5;

    [Tooltip("Adress of the prefab")]
    [SerializeField] private string m_patronLoadAddress = "Prefabs/Rabbit";

    [Tooltip("The total amount of the spawned rabbits")]
    [SerializeField] private int m_count = 0;

    private MyArray<GameObject> m_agentArray;

    [SerializeField] private RabbitPatternData m_rabbitPatternData = null;
    [SerializeField] private RabbitGrowthData m_rabbitGrowthData = null;

    // Start is called before the first frame update
    void Start()
    {
        var rabbits = GameObject.FindObjectsOfType<AiBrain>();
        List <GameObject> list= new List<GameObject>();
        foreach (var item in rabbits)
        {
            list.Add(item.gameObject);
        }

        if(list.Count > 0)
        {
            m_agentArray = new MyArray<GameObject>(list);
        }
        else
        {
            m_agentArray = new MyArray<GameObject>();
        }
    }

    // Update is called once per frame
    void Update()
    {
        if(m_count < m_closeCount)
        {
            if (m_elapsedTime > m_timer)
            {
                SpawnRandomAgent();
                m_elapsedTime -= m_timer;
            }
            else
            {
                m_elapsedTime += Time.deltaTime;
            }
        }
    }

    public void SpawnRandomAgent()
    {
        GameObject patron =  Instantiate(Resources.Load(m_patronLoadAddress), transform) as GameObject;
        RabbitGrowInfo theRabbit = patron.GetComponent<RabbitGrowInfo>();
        //random material
        int max = m_rabbitPatternData.m_rabbitPatternList.Count;
        int min = 0;
        int random = XorshiftRNG.Instance.GetRange(min, max);
        Material randMat = m_rabbitPatternData.m_rabbitPatternList[random].m_material;
        theRabbit.SetMaterial(randMat);

        //rand stat data
        StatManager stats = patron.GetComponent<StatManager>();
        stats.GetRandomStat();

        //rand grow info
        m_rabbitGrowthData.SetRandomGrowData(theRabbit);

        patron.transform.SetParent(null);
        m_agentArray.Add(patron);
        m_count++;
    }

    public void DestroyAgent()
    {
        int count = m_agentArray.Count();
        if(count == 0)
        {
            return;
        }

        if(count == 1)
        {
            DestroyAgent(0);
            return;
        }

        DestroyAgent(count - 1);
    }

    /// <summary>
    /// a specific agent
    /// </summary>
    /// <param name="theAgent"></param>
    public void DestroyAgent(GameObject theAgent)
    {
        m_agentArray.Delete(theAgent);
    }

    private void DestroyAgent(int index)
    {
        Destroy(m_agentArray[index]);
        m_agentArray.Remove(index);
    }
}
