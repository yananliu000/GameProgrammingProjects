using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RabbitGrowInfo : MonoBehaviour
{
    [SerializeField] float m_size = 2;
    [SerializeField] public float m_weight = 4;
    [SerializeField] public int m_days = 1;
    [SerializeField] GameObject m_materialHolder;
    [SerializeField] public RabbitGrowthData.EGrowthState m_growState;

    public float Size
    {
        set
        {
            m_size = value;
            transform.localScale = new Vector3(m_size, m_size, m_size);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        Size = m_size;
    }

    public void SetMaterial(Material value)
    {
        m_materialHolder.GetComponent<SkinnedMeshRenderer>().material = value;
    }
}
