using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Yanan Liu
/// Designer can drag and drop the component on any gameobj to create an empty surface
/// I would suggest to create an empty gameobject and it slight above or next to the tranform you want the surface to be
/// </summary>
public class LandableSurface : MonoBehaviour
{
    public enum ESurfaceType
    {
        kUndefined,
        kBack,
        kFront,
        kLeft,
        kRight,
        kTop,
        kFloor
    }

    //the radius range of the surface
    [SerializeField] public float m_radius = 1;

    //which side the surface is at: determines which axies whill have randomization
    [SerializeField] public ESurfaceType m_type = ESurfaceType.kUndefined;
}
