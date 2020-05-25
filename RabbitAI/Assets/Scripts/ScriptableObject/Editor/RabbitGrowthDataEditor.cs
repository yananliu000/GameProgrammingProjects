using System;
using System.Collections.Generic;
using UnityEditor;
using UnityEditorInternal;
using UnityEngine;

[CustomEditor(typeof(RabbitGrowthData))]
public class RabbitGrowthDataEditor : Editor
{
    SerializedProperty m_growthDataList;

    ReorderableList m_list;

    private Dictionary<string, ReorderableList> innerListDict = new Dictionary<string, ReorderableList>();

    private void OnEnable()
    {
        m_growthDataList = serializedObject.FindProperty("m_growthStateData");

        // setupt the outer list
        m_list = new ReorderableList(serializedObject, m_growthDataList)
        {
            displayAdd = true,
            displayRemove = true,
            draggable = true,

            drawHeaderCallback = rect =>
            {
                EditorGUI.LabelField(rect, "RabbitGrowthData");
            },

            drawElementCallback = (rect, index, a, h) =>
            {
                // get outer element
                var element = m_growthDataList.GetArrayElementAtIndex(index);
                var InnerList = element.FindPropertyRelative("m_growthChart");

                //set up the inner list
                string listKey = element.propertyPath;

                ReorderableList innerReorderableList;

                if (innerListDict.ContainsKey(listKey))
                {
                    // fetch the reorderable list in dict
                    innerReorderableList = innerListDict[listKey];
                }
                else
                {
                    // create reorderabl list and store it in dict
                    innerReorderableList = new ReorderableList(element.serializedObject, InnerList)
                    {
                        displayAdd = true,
                        displayRemove = true,
                        draggable = true,

                        drawHeaderCallback = innerRect =>
                        {
                            EditorGUI.LabelField(innerRect, "WeightSizeChart");
                        },

                        drawElementCallback = (innerRect, innerIndex, innerA, innerH) =>
                        {
                            // Get element of inner list
                            var innerElement = InnerList.GetArrayElementAtIndex(innerIndex);

                            EditorGUI.LabelField(new Rect(innerRect.x, innerRect.y, 100, EditorGUIUtility.singleLineHeight), "size");

                            EditorGUI.PropertyField(
                                new Rect(innerRect.x + 30, innerRect.y, 30, EditorGUIUtility.singleLineHeight),
                                innerElement.FindPropertyRelative("m_size"),
                                GUIContent.none
                            );

                            EditorGUI.PropertyField(
                                new Rect(innerRect.x + 70, innerRect.y, 60, EditorGUIUtility.singleLineHeight),
                                innerElement.FindPropertyRelative("m_sizeState"),
                                GUIContent.none
                            );

                            EditorGUI.LabelField(new Rect(innerRect.x + 140, innerRect.y, 100, EditorGUIUtility.singleLineHeight), "weight");

                            EditorGUI.PropertyField(
                               new Rect(innerRect.x + 190, innerRect.y, 30, EditorGUIUtility.singleLineHeight),
                               innerElement.FindPropertyRelative("m_weight"),
                               GUIContent.none
                           );

                            EditorGUI.PropertyField(
                              new Rect(innerRect.x + 230, innerRect.y, 60, EditorGUIUtility.singleLineHeight),
                              innerElement.FindPropertyRelative("m_weightState"),
                              GUIContent.none
                          );
                        }
                    };
                    innerListDict[listKey] = innerReorderableList;
                }

                //leave spacing and draw other variables
                var outerVariablesHeight = (InnerList.arraySize + 3) * EditorGUIUtility.singleLineHeight;

                EditorGUI.LabelField(new Rect(rect.x, rect.y + outerVariablesHeight, 100, EditorGUIUtility.singleLineHeight), "State");

                EditorGUI.PropertyField(
                        new Rect(rect.x + 50, rect.y + outerVariablesHeight, 80, EditorGUIUtility.singleLineHeight),
                        element.FindPropertyRelative("m_state"),
                        GUIContent.none
                    );

                EditorGUI.LabelField(new Rect(rect.x + 140, rect.y + outerVariablesHeight, 100, EditorGUIUtility.singleLineHeight), "Next State");

                EditorGUI.PropertyField(
                        new Rect(rect.x + 210, rect.y + outerVariablesHeight, 80, EditorGUIUtility.singleLineHeight),
                        element.FindPropertyRelative("m_nextState"),
                        GUIContent.none
                    );

                EditorGUI.LabelField(new Rect(rect.x + 300, rect.y + outerVariablesHeight, 100, EditorGUIUtility.singleLineHeight), "Days");

                EditorGUI.PropertyField(
                    new Rect(rect.x + 340, rect.y + outerVariablesHeight, 40, EditorGUIUtility.singleLineHeight),
                    element.FindPropertyRelative("m_days"),
                    GUIContent.none
                );

                // Setup the inner list
                var height = outerVariablesHeight + 5 * EditorGUIUtility.singleLineHeight;
                innerReorderableList.DoList(new Rect(rect.x, rect.y, rect.width, height));
            },

            elementHeightCallback = index =>
            {
                var element = m_growthDataList.GetArrayElementAtIndex(index);

                var innerList = element.FindPropertyRelative("m_growthChart");

                return (innerList.arraySize + 4) * EditorGUIUtility.singleLineHeight;
            }
        };
    }

    //This is the function that makes the custom editor work
    public override void OnInspectorGUI()
    {
        serializedObject.Update();
        m_list.DoLayoutList();
        serializedObject.ApplyModifiedProperties();
    }
}

