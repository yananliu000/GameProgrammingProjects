using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Context 
{
    public AiBrain m_agent = null;
    public ObjectManager m_objManager = null;
    public PopulationManager m_spawner = null;
    public Context(AiBrain patron, ObjectManager objManager, PopulationManager spawner)
    {
        m_agent = patron;
        m_objManager = objManager;
        m_spawner = spawner;
    }
}
