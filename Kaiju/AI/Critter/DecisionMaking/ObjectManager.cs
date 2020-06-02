using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager : MonoBehaviour
{
    public List<AiTarget> m_objects = null;

    public void UpdateAiTargetsList()
    {
        m_objects = new List<AiTarget>(FindObjectsOfType<AiTarget>());
    }

    public void AddIntoObjectList(AiTarget target)
    {
        m_objects.Add(target);
    }

    public void RemoveFromObjectList(AiTarget target)
    {
        for (int i = 0; i < m_objects.Count; i++)
        {
            if(m_objects[i] == target)
            {
                m_objects.RemoveAt(i);
                return;
            }
        }
#if DEBUG
        Debug.LogError("The ai object is not in the object list.");
#endif
    }
}
