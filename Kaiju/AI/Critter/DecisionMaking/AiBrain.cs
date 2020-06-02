using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Yanan Liu
/// Agent wil pick the best action based on action scores. 
/// The original thougth is to utilize utility theory to make the ai be able to choose who to attack: based on player hp, player distance, player damage. 
/// But for the 2020 Spring, the project cancelled all the multiplayer features temporarily becaues of COVID 19, so the functionality hasn't been developed. 
/// </summary>
public class AiBrain : MonoBehaviour
{
    class ScorePair
    {
        public float m_score;
        public ActionTargetPair m_actionTargetPair;
        public ScorePair(float score, ActionTargetPair actionTargetPair)
        {
            m_score = score;
            m_actionTargetPair = actionTargetPair;
        }
    }

    Context m_context = null;
    public Action m_currentAction;
    public Context Context
    {
        get => m_context;
    }

    void Start()
    {
        m_currentAction = null;
        m_context = new Context(this, FindObjectOfType<ObjectManager>(), FindObjectOfType<AIManager>());
    }

    /// <summary>
    /// The function will make an decision for the agent: what to do next 
    /// </summary>
    public void MakeDecision()
    {
        if (m_context.m_objManager.m_objects.Count == 0)
        {
#if DEBUG
            Debug.LogWarning("no alive player");
#endif
            return;
        }
        ActionTargetPair result = FindBestAction(m_context);
        m_currentAction = result.m_actionDef.CreateAction(this, result.m_aiTarget);
    }

    
    /// <summary>
    /// The function will pick the best action for the AI from all doable actions 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    public ActionTargetPair FindBestAction(Context context)
    {
        List<ScorePair> scores = new List<ScorePair>();

        //    # score everything
        foreach (var obj in context.m_objManager.m_objects)
        {
            //TODO: ignore the player is the health is 00 

            if (obj.isActiveAndEnabled)
            {
                foreach (var actionDef in obj.ActionDefinitionArray)
                {
                    ActionTargetPair pair = new ActionTargetPair(obj, actionDef);
                    float score = Score(pair, context);
                    ScorePair scorePair = new ScorePair(score, pair);
                    scores.Add(scorePair);
                }
            }
        }

        //    # return the "best" score
        return SelectScoredAction(scores);
    }

    /// <summary>
    /// The function will score an action 
    /// </summary>
    /// <param name="actionTargetPair"></param>
    /// <param name="context"></param>
    /// <returns></returns>
    float Score(ActionTargetPair actionTargetPair, Context context)
    {
        List<float> allScores = new List<float>();
        foreach (var decisionFactor in actionTargetPair.m_decisionFactors)
        {
            float score = decisionFactor.Score(actionTargetPair, context);
            allScores.Add(score);
        }

        //  #  finalScore = GeometricMean(allScores)
        float finalScore = MyMath.GeometricMean(allScores);
        return finalScore;
    }

    /// <summary>
    /// The selction 
    /// </summary>
    /// <param name="scores"></param>
    /// <returns></returns>
    ActionTargetPair SelectScoredAction(List<ScorePair> scores)
    {
        // # Option 1: Return the best
        // # This is good for "good" AI or competetive stuff.

        ScorePair maxPair = scores[0];
        for (int i = 1; i < scores.Count; i++)
        {
            if (scores[i].m_score > maxPair.m_score)
            {
                maxPair = scores[i];
            }
        }

        return maxPair.m_actionTargetPair;

        // # Option 2: Return a good result
        // add randomness here 
    }
}
