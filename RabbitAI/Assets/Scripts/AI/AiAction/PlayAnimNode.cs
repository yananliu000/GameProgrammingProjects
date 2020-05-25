using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class PlayAnimNode : ActionNodeBase
{
    public string m_animationName;

    public PlayAnimNode(string animName)
    {
        m_nodeType = ENodeType.kPlayAnimation;
        m_animationName = animName;
    }

    public sealed override bool Execute(AiBrain agent)
    {
        agent.GetComponent<Animator>().Play(m_animationName);
        return true;
    }
}
