using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//Assets  -> Create
[CreateAssetMenu(menuName = "GenerateRabbitData/Pattern")]
public class RabbitPatternData : ScriptableObject
{
    public enum EPatternType
    {
        kYellow,
        kWhite,
        kYellowWhiteHybird,
        kBlack,
    }

    [System.Serializable]
    public struct Pattern
    {
        public Material m_material;
        public EPatternType m_type;
    }

    public List<Pattern> m_rabbitPatternList = new List<Pattern>();    
}

