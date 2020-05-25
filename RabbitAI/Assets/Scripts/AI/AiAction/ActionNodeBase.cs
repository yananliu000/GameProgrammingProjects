using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;

/* Unity Polymorphism 
 * :<
 * after trying a few hours, I think it's unable to get "really" polymorphism 
 * in unity editor unless I do the serialization myself or use an uniform format for all nodes.
 * So I didn't make actionDefinitions as scriptabel object but load them from xml instead. 
 */

[System.Serializable]
public class ActionNodeBase 
{
    public enum ENodeType
    {
        kStatModify, 
        kPlayAnimation,  
        kActionNodeTypeNum,
        kDefault

    }

    public ENodeType m_nodeType = ENodeType.kDefault;

    public virtual bool Execute(AiBrain agent)
    {
        return true;
    }
}
