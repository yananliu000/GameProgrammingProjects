using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Context 
{
    public AiBrain m_patron = null;
    public ObjectManager m_objManager = null;
    public AIManager m_aiManager = null;
    public Context(AiBrain patron, ObjectManager objManager, AIManager aiManager)
    {
        m_patron = patron;
        m_objManager = objManager;
        m_aiManager = aiManager;
    }
}
