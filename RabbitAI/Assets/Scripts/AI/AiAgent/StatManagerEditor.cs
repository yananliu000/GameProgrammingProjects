using UnityEngine;
using UnityEditor;
using UnityEditorInternal; 

[CustomEditor(typeof(StatManager))]
public class StatManagerEditor : Editor
{
    SerializedProperty m_statList;

    ReorderableList m_list;

    private void OnEnable()
    {
        m_statList = serializedObject.FindProperty("m_stats");
        m_list = new ReorderableList(serializedObject, m_statList, true, true, true, true);
        m_list.drawElementCallback = DrawListItems;
        m_list.drawHeaderCallback = DrawHeader;
    }

    void DrawListItems(Rect rect, int index, bool isActive, bool isFocused)
    {
        SerializedProperty element = m_list.serializedProperty.GetArrayElementAtIndex(index); 
        
        EditorGUI.PropertyField(
            new Rect(rect.x, rect.y, 100, EditorGUIUtility.singleLineHeight),
            element.FindPropertyRelative("m_type"),
            GUIContent.none
        );
      
        EditorGUI.LabelField(new Rect(rect.x + 120, rect.y, 100, EditorGUIUtility.singleLineHeight), "decayRate");

        EditorGUI.PropertyField(
            new Rect(rect.x + 200, rect.y, 30, EditorGUIUtility.singleLineHeight),
            element.FindPropertyRelative("m_decayRate"),
            GUIContent.none
        );

       EditorGUI.LabelField(new Rect(rect.x + 240, rect.y, 100, EditorGUIUtility.singleLineHeight), "Max");

       EditorGUI.PropertyField(
           new Rect(rect.x + 270, rect.y, 30, EditorGUIUtility.singleLineHeight),
           element.FindPropertyRelative("m_max"),
           GUIContent.none
       );

        EditorGUI.LabelField(new Rect(rect.x + 310, rect.y, 100, EditorGUIUtility.singleLineHeight), "Min");

        EditorGUI.PropertyField(
            new Rect(rect.x + 340, rect.y, 20, EditorGUIUtility.singleLineHeight),
            element.FindPropertyRelative("m_min"),
            GUIContent.none
        );

        EditorGUI.LabelField(new Rect(rect.x + 370, rect.y, 100, EditorGUIUtility.singleLineHeight), "Value");

        EditorGUI.PropertyField(
            new Rect(rect.x + 410, rect.y, 30, EditorGUIUtility.singleLineHeight),
            element.FindPropertyRelative("m_value"),
            GUIContent.none
        );

        EditorGUI.LabelField(new Rect(rect.x + 450, rect.y, 100, EditorGUIUtility.singleLineHeight), "Multiplier");

        EditorGUI.PropertyField(
            new Rect(rect.x + 510, rect.y, 20, EditorGUIUtility.singleLineHeight),
            element.FindPropertyRelative("m_multiplier"),
            GUIContent.none
        );

    }

    void DrawHeader(Rect rect)
    {
        string name = "StatList";
        EditorGUI.LabelField(rect, name);
    }

    //This is the function that makes the custom editor work
    public override void OnInspectorGUI()
    {
        serializedObject.Update();
        m_list.DoLayoutList();
        serializedObject.ApplyModifiedProperties();
    }
}

