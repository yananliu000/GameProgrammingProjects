using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class EnumTool
{
    //https://stackoverflow.com/questions/79126/create-generic-method-constraining-t-to-an-enum
    public static T EnumParse<T>(string value, T defaultValue) where T : struct, System.IConvertible
    {
        if (!typeof(T).IsEnum)
        {
            throw new System.ArgumentException("T must be an enumerated type");
        }
        if (string.IsNullOrEmpty(value))
        {
            return defaultValue;
        }

        foreach (T item in System.Enum.GetValues(typeof(T)))
        {
            if (item.ToString().Equals(value.Trim()))
            {
                return item;
            }
        }

        return defaultValue;
    }
}
