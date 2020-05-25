using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AiBrain : MonoBehaviour
{
    private AiNavigation m_navigation;

    [Tooltip("Current action of the agent")]
    [SerializeField] protected Action m_currentAction;

    public Action CurrentAction { get => m_currentAction; }
    [SerializeField] private GameObject m_meshGroup;
        
    public GameObject MeshGroup
    {
        get { return m_meshGroup; }
    }

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

    private Context m_context = null;

    #region Initialize
    void Start()
    {
        //navigation
        m_navigation = GetComponent<AiNavigation>();

#if DEBUG
        if (m_navigation == null)
        {
            Debug.LogError("fail to get MoveTo component",  this.gameObject);
        }
#endif
        //context
        m_context = new Context(this, ObjectManager.Instance, PopulationManager.Instance);

        //actions
        m_currentAction = null;
    }

    
    #endregion

    void Update()
    {
        //update action 
        if (m_currentAction != null)
        {
            if(m_navigation.IsArrived)
            {
                if (m_currentAction.Update(Time.deltaTime))
                {
                    //make another decision
                    MakeDecision();
                }
            }
        }
        else
        {
            MakeDecision();
        }
    }

    #region Utility Theory
    void MakeDecision()
    {
        ActionTargetPair result = FindBestAction(m_context);
        if(result != null)
        {
            m_navigation.Goal = result.m_aiTarget.transform;
            m_currentAction = result.m_actionDef.CreateAction(this, result.m_aiTarget);
        }
    }
    
    public ActionTargetPair FindBestAction(Context context)
    {
        List<ScorePair> scores = new List<ScorePair>();

        //    # score everything
        if(context.m_objManager.m_objects.Count > 0)
        {
            foreach (var obj in context.m_objManager.m_objects)
            {
                if (obj != null)
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
        }
        else
        {
#if DEBUG
            Debug.LogWarning("There's no interactable object.", this.gameObject);
#endif 
            return null;
        }

        //    # return the "best" score
        return SelectScoredAction(scores);
    }
    
    float Score(ActionTargetPair actionTargetPair, Context context)
    {
        List<float> allScores = new List<float>();
        for (int i = 0; i < actionTargetPair.m_decisionFactors.Count; i++)
        {
            float score = actionTargetPair.m_decisionFactors[i].Score(actionTargetPair, context);
            allScores.Add(score);
        }

        //  #  finalScore = GeometricMean(allScores)
        float finalScore = MyMath.GeometricMean(allScores);
        return finalScore;
    }
   
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
    #endregion

    private void OnDestroy()
    {
        PopulationManager.Instance.DestroyAgent(this.gameObject);
    }
}
