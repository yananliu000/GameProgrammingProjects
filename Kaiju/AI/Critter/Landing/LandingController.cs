using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Yanan Liu
/// The controller will assign a randomly landable postion (LandResult) from its landing surfaces.
/// Landing controllers should be owned by landing manager. 
/// </summary>
public class LandingController : MonoBehaviour
{
    //The randomly landable postion format 
    public class LandResult
    {
        //position
        public Vector3 m_landingPoint;

        //rotation
        public Quaternion m_landingAngle;

        //constructor
        public LandResult(Vector3 point, Quaternion angle)
        {
            m_landingAngle = angle;
            m_landingPoint = point;
        }
    }

    //the landing surface array
    [SerializeField] private List<LandableSurface> m_landingArray;

    //randomization of the landing rotation 
    [SerializeField] private float m_landingAngleRandomRange = 20;
    
    private void Start()
    {
        m_landingArray = new List<LandableSurface>();
        m_landingArray.AddRange(GetComponentsInChildren<LandableSurface>());
    }

    /// <summary>
    /// Get a landing position from the landing controller
    /// </summary>
    /// <returns></returns>
    public LandResult GetLandableSurface()
    {
        if(m_landingArray.Count == 0)
        {
#if DEBUG
            Debug.LogError("You need to set the landable surfaces first.");
#endif
        }
        else
        {
            //return a random landable surface 
            int randIndex = Random.Range(0, m_landingArray.Count);
            LandableSurface surface = m_landingArray[randIndex];

            //Todo:
            float randomRot = Random.Range(-m_landingAngleRandomRange, m_landingAngleRandomRange);

            Vector2 randV2 = Random.insideUnitCircle * surface.m_radius;
            Vector3 position = Vector3.zero;
            Quaternion angle = Quaternion.identity;
            switch (surface.m_type)
            {
                case LandableSurface.ESurfaceType.kUndefined:
#if DEBUG
                    Debug.LogError("Error, the type of surface is undefined.");
#endif
                    return null;

                case LandableSurface.ESurfaceType.kBack: 
                case LandableSurface.ESurfaceType.kFront:
                    position = surface.transform.position + new Vector3(randV2.x, randV2.y, 0);
                    angle = Quaternion.Euler(0 + randomRot, 90 , -90 ) ;
                    break;

                case LandableSurface.ESurfaceType.kLeft: 
                case LandableSurface.ESurfaceType.kRight:
                    position = surface.transform.position + new Vector3(0, randV2.x, randV2.y);
                    angle = Quaternion.Euler(0 + randomRot, 0 , -90);
                    break;

                case LandableSurface.ESurfaceType.kFloor: 
                    position = surface.transform.position + new Vector3(randV2.x, 0, randV2.y);
                    angle = Quaternion.Euler(0, -90 + randomRot, 0);

                    break;
                case LandableSurface.ESurfaceType.kTop:
                    position = surface.transform.position + new Vector3(randV2.x, 0, randV2.y);
                    angle = Quaternion.Euler(0 , -90 + randomRot, -180 );
                    break;

                default:
                    return null;
            }
            return new LandResult(position, angle);
        }
        return null;
    }
}
