using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//limit the range of T to class, so the default value can be null
class MyArray<T> where T: class 
{
    private List<T> m_myList = null;
    public T this[int key]
    {
        get 
        {
            return IsIndexValid(key) ? m_myList[key] : null;
        }

        set
        {
            if(IsIndexValid(key))
            {
                m_myList[key] = value;
            }
        }
            
    }

    bool IsIndexValid(int key)
    {
        return key >= 0 && key < m_myList.Count;
    }
    public MyArray(List<T> list)
    {
        m_myList = list;
    }

    public MyArray()
    {
        m_myList = new List<T>();
    }
    public void Add(T value)
    {
        //find empty slot for new value
        for (int i = 0; i < m_myList.Count; i++)
        {
            if(m_myList[i] == null)
            {
                m_myList[i] = value;
                return;
            }
        }

        //if none, add to the end
        m_myList.Add(value);
    }

    public void Delete(T value)
    {
        //find where is the value, set it to null
        for (int i = 0; i < m_myList.Count; i++)
        {
            if (m_myList[i] == value)
            {
                m_myList[i] = null;
                return;
            }
        }
    }

    public void Remove(int index)
    {
        //varify the index and set the slot to null 
        if(IsIndexValid(index))
        {
            m_myList[index] = null;
        }
        else
        {
#if DEBUG
            Debug.LogWarning("Invalid index");
#endif
        }
    }

    public int Count()
    {
        int count = 0;
        foreach (var item in m_myList)
        {
            if(item != null)
            {
                count++;
            }
        }

        return count;
    }
}
