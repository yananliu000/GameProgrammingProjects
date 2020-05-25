using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectManager : SingletonMonoBehavior<ObjectManager>
{
    public List<AiTarget> m_objects = new List<AiTarget>();

    public void RemoveFromObjectList(AiTarget theTarget)
    {
        for (int i = 0; i < m_objects.Count; i++)
        {
            if(m_objects[i] == theTarget)
            {
                m_objects[i] = null;
                return;
            }
        }
    }

    public void AddIntoObjectList(AiTarget theTarget)
    {
        //check empty slot
        for (int i = 0; i < m_objects.Count; i++)
        {
            if (m_objects[i] == null)
            {
                m_objects[i] = theTarget;
                return;
            }
        }

        //new slot
        m_objects.Add(theTarget);
    }
}
