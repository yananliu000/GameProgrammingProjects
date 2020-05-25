using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StatManager : MonoBehaviour
{
    [Tooltip("Stats of the agent")]
    [SerializeField] private List<StatBase> m_stats = new List<StatBase>();

    public StatBase FindStatByType(StatBase.EStatType type)
    {
        //in optimal cases, the index of stat = (int) the enum type 
        int defaultIndex = (int)type;
        if (defaultIndex >= 0 && defaultIndex < m_stats.Count)
        {
            StatBase defaultStat = m_stats[defaultIndex];
            if (defaultStat.m_type == type)
            {
                return defaultStat;
            }
        }

        //if not, loop the list to find it and debug warning
        foreach (var stat in m_stats)
        {
            if (stat.m_type == type)
            {
#if DEBUG
                Debug.LogWarning("The order of the state list is not the optimal.", this.gameObject);
#endif
                return stat;

            }
        }


#if DEBUG
        Debug.LogError("The stat type is undefined", this.gameObject);
#endif
        return null;
    }

    // Update is called once per frame
    void Update()
    {
        //update stat
        for (int i = 0; i < m_stats.Count; i++)
        {
            m_stats[i].Update(Time.deltaTime);
        }
    }

    private void Reset()
    {
        //stats 
        m_stats.Clear();

        for (int i = 0; i < (int)StatBase.EStatType.kStatsNum; i++)
        {
            m_stats.Add(new StatBase((StatBase.EStatType)i));
        }
    }

    public void GetRandomStat()
    {
        foreach (var item in m_stats)
        {
            item.Value = XorshiftRNG.Instance.GetRange(item.Min, item.Max);
        }
    }
}
