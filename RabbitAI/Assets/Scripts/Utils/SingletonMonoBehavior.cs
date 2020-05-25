using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingletonMonoBehavior<T>: MonoBehaviour where T : class
{
    protected SingletonMonoBehavior() { }
    
    class SingletonCreator
    {
        static SingletonCreator() { }
        // Private object instantiated with private constructor
        internal static readonly T m_instance = FindObjectOfType(typeof(T)) as T;
    }

    public static T Instance
    {
        get 
        {
            if (SingletonCreator.m_instance == null)
            {
#if DEBUG
                Debug.LogError($"There needs to be one active {typeof(T).Name} script on a GameObject in your scene.");
#endif
            }
            return SingletonCreator.m_instance; 
        }
    }
}
