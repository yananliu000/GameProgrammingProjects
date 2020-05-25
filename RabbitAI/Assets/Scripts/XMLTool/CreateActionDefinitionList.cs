using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using System.Xml;

public class CreateActionDefinitionList
{
    private static string m_xmlPath = Application.streamingAssetsPath + "/AiActions.xml";
    private static string m_actionDefinitionElement = "actionDefinition";
    private static string m_rootElement = "root";
    private static string m_typeAttribute = "type";
    private static string m_durationAttribute = "duration";
    private static string m_beginNodesElement = "beginNodesList";
    private static string m_endNodesElement = "endNodesList";
    private static string m_decisionFactorsElement = "decisionFactors";
    private static string m_decisionFactorTypeElement = "decisionFactorType";
    private static string m_beginNodeElement = "beginNode";
    private static string m_endNodeElement = "endNode";
    private static string m_actionNodeTypeAttribute = "nodeType";
    private static string m_statTypeAttribute = "statType";
    private static string m_valueAttribute = "value";
    private static string m_animNameAttribute = "animName";

    #region Read XML: helper functions
    /// <summary>
    /// read an ActionDefinition from a xml element
    /// </summary>
    /// <param name="actionDefinitionNode"></param>
    /// <returns></returns>
    private static ActionDefinition ReadActionDefinitionElement(XmlElement actionDefinitionNode)
    {
        string actionTypeString = actionDefinitionNode.GetAttribute(m_typeAttribute);
        ActionDefinition.EActionType actionType = EnumTool.EnumParse<ActionDefinition.EActionType>(actionTypeString, ActionDefinition.EActionType.kActionTypeNum);
        float duration = float.Parse(actionDefinitionNode.GetAttribute(m_durationAttribute));

        List<ActionNodeBase> beginNodes = new List<ActionNodeBase>();
        List<ActionNodeBase> endNodes = new List<ActionNodeBase>();
        List<StatBase.EStatType> decisionFactors = new List<StatBase.EStatType>();

        XmlElement beginNodesElement = (XmlElement) actionDefinitionNode.SelectSingleNode(m_beginNodesElement);
        XmlElement endNodesElement = (XmlElement) actionDefinitionNode.SelectSingleNode(m_endNodesElement);
        XmlElement decisionFactorsElement = (XmlElement) actionDefinitionNode.SelectSingleNode(m_decisionFactorsElement);
         
        foreach (XmlElement element in beginNodesElement.GetElementsByTagName(m_beginNodeElement))
        {
            ReadActionBaseNodeElement(beginNodes, element);
        }

        foreach (XmlElement element in endNodesElement.GetElementsByTagName(m_endNodeElement))
        {
            ReadActionBaseNodeElement(endNodes, element);
        }

        foreach (XmlElement item in decisionFactorsElement.GetElementsByTagName(m_decisionFactorTypeElement))
        {
            decisionFactors.Add(EnumTool.EnumParse<StatBase.EStatType>(item.InnerText, StatBase.EStatType.kNone));
        }

        ActionDefinition definition = new ActionDefinition(actionType, duration,beginNodes, endNodes, decisionFactors);
        return definition;
    }

    /// <summary>
    /// read an ActionBaseNode from a xml element
    /// </summary>
    /// <param name="list"></param>
    /// <param name="element"></param>
    static void ReadActionBaseNodeElement(List<ActionNodeBase> list, XmlElement element)
    {
        ActionNodeBase node = null;
        ActionNodeBase.ENodeType nodeType = EnumTool.EnumParse<ActionNodeBase.ENodeType>(element.GetAttribute(m_actionNodeTypeAttribute), ActionNodeBase.ENodeType.kActionNodeTypeNum);
        switch (nodeType)
        {
            case ActionNodeBase.ENodeType.kStatModify:
                StatBase.EStatType statType = EnumTool.EnumParse<StatBase.EStatType>(element.GetAttribute(m_statTypeAttribute), StatBase.EStatType.kStatsNum);
                float value = float.Parse(element.GetAttribute(m_valueAttribute));
                node = new StatModifyNode(statType, value);
                break;
            case ActionNodeBase.ENodeType.kPlayAnimation:
                string animName = element.GetAttribute(m_animNameAttribute);
                node = new PlayAnimNode(animName);
                break;
            default:
#if DEBUG
                Debug.LogError("invalid action node type");
#endif
                break;
        }

        if(node != null)
        {
            list.Add(node);
        }
    }
    #endregion

    #region Write XML: helper functions
    /// <summary>
    /// write an ActionBaseNode to xml
    /// </summary>
    /// <param name="actionNode"></param>
    /// <param name="element"></param>
    static void WriteActionNode(ActionNodeBase actionNode, XmlElement element)
    {
        element.SetAttribute(m_actionNodeTypeAttribute, actionNode.m_nodeType.ToString());

        switch (actionNode.m_nodeType)
        {
            case ActionNodeBase.ENodeType.kStatModify:
                StatModifyNode modifyNode = (StatModifyNode)actionNode;
                element.SetAttribute(m_statTypeAttribute, modifyNode.m_stateType.ToString());
                element.SetAttribute(m_valueAttribute, modifyNode.m_value.ToString());

                break;
            case ActionNodeBase.ENodeType.kPlayAnimation:
                PlayAnimNode Animnode = (PlayAnimNode)actionNode;
                element.SetAttribute(m_animNameAttribute, Animnode.m_animationName.ToString());
                break;
            default:
#if DEBUG
                Debug.LogError("Unrecognizable action node type");
#endif
                break;
        }
    }

    /// <summary>
    /// Write xml file form a list of action definitions
    /// </summary>
    /// <param name="actionDefinitions"></param>
    static void WriteAiActionXML(List<ActionDefinition> actionDefinitions)
    {
        //create document
        XmlDocument xml = new XmlDocument();

        //create root
        XmlElement root = xml.CreateElement(m_rootElement);

        //for each actionDefinition => an element
        foreach (var definition in actionDefinitions)
        {
            XmlElement definitionElement = xml.CreateElement(m_actionDefinitionElement);

            //attributes 
            definitionElement.SetAttribute(m_typeAttribute, definition.m_type.ToString());
            definitionElement.SetAttribute(m_durationAttribute, definition.m_duration.ToString());

            //sub-elements
            XmlElement beginNodesElement = xml.CreateElement(m_beginNodesElement);
            XmlElement endNodesElement = xml.CreateElement(m_endNodesElement);
            XmlElement decisionFactorsElement = xml.CreateElement(m_decisionFactorsElement);

            definitionElement.AppendChild(beginNodesElement);
            definitionElement.AppendChild(endNodesElement);
            definitionElement.AppendChild(decisionFactorsElement);

            foreach (var node in definition.m_beginActionNodes)
            {
                XmlElement nodeElement = xml.CreateElement(m_beginNodeElement);
                beginNodesElement.AppendChild(nodeElement);
                WriteActionNode(node, nodeElement);
            }

            foreach (var node in definition.m_endActionNodes)
            {
                XmlElement nodeElement = xml.CreateElement(m_endNodeElement);
                endNodesElement.AppendChild(nodeElement);
                WriteActionNode(node, nodeElement);
            }

            foreach (var decisionFactor in definition.m_decisionFactorsType)
            {
                XmlElement node = xml.CreateElement(m_decisionFactorTypeElement);
                node.InnerText = decisionFactor.ToString();
                decisionFactorsElement.AppendChild(node);
            }
            root.AppendChild(definitionElement);
            xml.AppendChild(root);

            //save
            xml.Save(m_xmlPath);
        }

    }
    #endregion


    #region Menu 
    /// <summary>
    /// Generate a default xml file
    /// </summary>
    [MenuItem("Tools/CreateAiActionXML: Default")]
    static void GenerateDefaultAiActionXML()
    {
        List<ActionDefinition> actionDefinitions = new List<ActionDefinition>();
        actionDefinitions.Add(
            new ActionDefinition
            (ActionDefinition.EActionType.kEat, 2
            , new List<ActionNodeBase>() { new PlayAnimNode("Eat") }
            , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kHunger, 30) }
            , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kHunger}
            ));

        actionDefinitions.Add(
            new ActionDefinition
            (ActionDefinition.EActionType.kDrink, 2
            , new List<ActionNodeBase>() { new PlayAnimNode("Eat") }
            , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kThirsty, 30) }
            , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kThirsty }
            ));

        actionDefinitions.Add(
           new ActionDefinition
           (ActionDefinition.EActionType.kSleep, 10
           , new List<ActionNodeBase>() { new PlayAnimNode("Idle") }
           , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kEnergy, 70) }
           , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kEnergy }
           ));

        actionDefinitions.Add(
          new ActionDefinition
          (ActionDefinition.EActionType.kPlay, 5
          , new List<ActionNodeBase>() { new PlayAnimNode("Damage") }
          , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kFun, 50) }
          , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kFun }
          ));

        actionDefinitions.Add(
          new ActionDefinition
          (ActionDefinition.EActionType.kBath, 4
          , new List<ActionNodeBase>() { new PlayAnimNode("Damage") }
          , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kHygiene, 50) }
          , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kHygiene }
          ));

        actionDefinitions.Add(
          new ActionDefinition
          (ActionDefinition.EActionType.kPooPoo, 3.5f
          , new List<ActionNodeBase>() { new PlayAnimNode("Idle") }
          , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kBladder, 100) }
          , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kBladder }
          ));

        actionDefinitions.Add(
        new ActionDefinition
        (ActionDefinition.EActionType.kTalk, 3
        , new List<ActionNodeBase>() { new PlayAnimNode("Damage") }
        , new List<ActionNodeBase>() { new StatModifyNode(StatBase.EStatType.kSocial, 30) }
        , new List<StatBase.EStatType>() { StatBase.EStatType.kDistance, StatBase.EStatType.kSocial }
        ));

        WriteAiActionXML(actionDefinitions);
    }
    #endregion

    public static List<ActionDefinition> GenerateActionDefinitionListFromXML()
    {
        //new list
        List<ActionDefinition> actionDefinitions = new List<ActionDefinition>();

        //load from xml
        XmlDocument xml = new XmlDocument();
        xml.Load(m_xmlPath);

        //gets all action definitions under root
        XmlNodeList xmlNodeList = xml.SelectSingleNode(m_rootElement).ChildNodes;

        foreach (XmlNode node in xmlNodeList)
        {
            var result = ReadActionDefinitionElement((XmlElement)node);
            if(result != null)
            {
                actionDefinitions.Add(result);
            }
        }

        return actionDefinitions;
    }
}

