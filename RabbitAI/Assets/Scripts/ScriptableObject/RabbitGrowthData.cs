using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Assets  -> Create
[CreateAssetMenu(menuName = "GenerateRabbitData/Growth")]
public class RabbitGrowthData : ScriptableObject
{
    public List<GrowthStateData> m_growthStateData = new List<GrowthStateData>();

    public enum EGrowthState
    {
        kNewborn,
        kSmall,
        kAdult,
        kOld,
        kGrowStateNum,
        kNull,
        kDefault,
    }

    public enum EWeight
    {
        kLight,
        kMedium,
        kHeavy,
    }

    public enum ESize
    {
        kSmall,
        kMedium,
        kLarge,
    }

    [System.Serializable]
    public struct WeightSizePair
    {
        public float m_size;
        public ESize m_sizeState;
        public float m_weight;
        public EWeight m_weightState;
    }

    [System.Serializable]
    public class GrowthStateData
    {
        public EGrowthState m_state = EGrowthState.kDefault;
        public EGrowthState m_nextState = EGrowthState.kDefault;

        public int m_days;
        public List<WeightSizePair> m_growthChart = new List<WeightSizePair>();

        public WeightSizePair GetMin()
        {
            return m_growthChart[0];
        }

        public WeightSizePair GetMax()
        {
            int index = m_growthChart.Count;
            return m_growthChart[index - 1];
        }

        public float GetSizeByWeight(float weight, float randRange)
        {
            float rand = XorshiftRNG.Instance.GetRange(0, randRange);

            foreach (var item in m_growthChart)
            {
                if(item.m_weight > weight)
                {
                    return item.m_size + rand;
                }
            }
            
            
            return m_growthChart[m_growthChart.Count - 1].m_size + rand;
        }

        public float GetWeightBySize(float size)
        {
            foreach (var item in m_growthChart)
            {
                if (item.m_size > size)
                {
                    return item.m_weight;
                }
            }

            return m_growthChart[m_growthChart.Count - 1].m_weight;
        }
    }

    public GrowthStateData FindGrowDataByState(EGrowthState state)
    {
        foreach (var item in m_growthStateData)
        {
            if(item.m_state == state)
            {
                return item;
            }
        }
        return null;
    }

    public void SetRandomGrowData(RabbitGrowInfo agent, float sizeRangRange = 0.1f, float weightRandRange = 0.1f)
    {
        EGrowthState randState = (EGrowthState) XorshiftRNG.Instance.GetRange(0, (int)EGrowthState.kGrowStateNum);

        //random state
        agent.m_growState = randState;

        GrowthStateData randGrowData = FindGrowDataByState(randState);

        if(randGrowData == null)
        {
#if DEBUG
            Debug.LogError("Inavlid grow data");
#endif
            return;
        }
        EGrowthState nextState = randGrowData.m_nextState;

        //rand days
        if (nextState != EGrowthState.kNull)
        {
            GrowthStateData NextGrowData = FindGrowDataByState(nextState);
            if(NextGrowData == null)
            {
#if DEBUG
                Debug.LogError("Invalid Grow data");
#endif
                return;
            }
            agent.m_days = XorshiftRNG.Instance.GetRange(randGrowData.m_days, NextGrowData.m_days);
        }
        else
        {
            agent.m_days = randGrowData.m_days + XorshiftRNG.Instance.GetRange(0, 10);
        }

        //rand weight and size
        float minWeight = randGrowData.m_growthChart[0].m_weight;
        float maxWeight = randGrowData.m_growthChart[randGrowData.m_growthChart.Count - 1].m_weight  + XorshiftRNG.Instance.GetRange(0, weightRandRange);
        agent.m_weight = XorshiftRNG.Instance.GetRange(minWeight, maxWeight);
        agent.Size = randGrowData.GetSizeByWeight(agent.m_weight, sizeRangRange);
    }
}
