using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class MyMath 
{
    static public float GeometricMean(List<float> arr)
    {
        int size = arr.Count;

        if(size == 0)
        {
            return 0;
        }

        // declare product variable and 
        // initialize it to 1. 
        float product = 1;

        // Compute the product of all the 
        // elements in the array. 
        for (int i = 0; i < size; i++)
            product = product * arr[i];

        // compute geometric mean through  
        // formula pow(product, 1/n) and 
        // return the value to main function. 
        float gm = (float)Mathf.Pow(product, (float)1 / size);
        return gm;
    }
}
