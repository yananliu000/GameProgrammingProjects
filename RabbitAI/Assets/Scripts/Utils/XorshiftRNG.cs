using UnityEngine.Assertions;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class XorshiftRNG: SingletonMonoBehavior<XorshiftRNG>
{
    [SerializeField] private bool m_useRandomSeed = false;
    [SerializeField] private uint m_seed;

    private void Awake()
    {
        //seed rng
        if(m_useRandomSeed)
        {
            m_seed = (uint)Random.Range(1, uint.MaxValue);
        }
        XorshiftRNG.Instance.Seed = m_seed;
    }

    class Xorshift32State
    {
        public uint m_value = 2019;
    }

    Xorshift32State m_state = new Xorshift32State();

    public uint Seed
    {
        get { return m_state.m_value; }
        set
        {
#if DEBUG
            Assert.IsTrue(value != 0, "Seed cannot be 0.");
#endif
            if (value != 0)
            {
                m_state.m_value = value;
            }
        }
    }

    private uint Next()
    {
        uint x = m_state.m_value;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return m_state.m_value = x;
    }

    public uint GetUInt()
    {
        Next();
        return m_state.m_value;
    }

    public int GetInt()
    {
        Next();
        return (int)(m_state.m_value % int.MaxValue);
    }

    /// <summary>
    /// inclusive low, exclusive high
    /// </summary>
    /// <param name="low"></param>
    /// <param name="high"></param>
    /// <returns></returns>
    public int GetRange(int low, int high)
    {
        Next();
#if DEBUG
        Assert.IsTrue(high > low, "high needs to be larger than low");
#endif
        return (int)(m_state.m_value % (uint)(high - low)) + low;
    }

    public float GetNorm()
    {
        Next();
        return (float)m_state.m_value / (float)uint.MaxValue;
    }

    public float GetRange(float low, float high)
    {
        Next();
#if DEBUG
        Assert.IsTrue(high > low, "high needs to be larger than low");
#endif
        float diff = high - low;
        float value = GetNorm() * diff;

        return value + low;
    }

    public bool GetBool()
    {
        Next();
        if(m_state.m_value % 2 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
