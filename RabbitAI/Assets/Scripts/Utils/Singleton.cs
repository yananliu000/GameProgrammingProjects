using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Singleton<T> where T : class, new()
{
    protected Singleton() { }

    class SingletonCreator
    {
        static SingletonCreator() { }
        internal static readonly T m_instance = new T();
    }

    public static T Instance
    {
        get { return SingletonCreator.m_instance; }
    }
}