#include "IComponent.h"
#include "../../Utility/MyLogger.h"
Engine::IComponent::Type Engine::IComponent::GetTypeFromElementName(const std::string & name)
{
	if (name == "transform")
	{
		return IComponent::Type::kTransform;
	}
	else if (name == "spriteRenderer")
	{
		return IComponent::Type::kSpriteRenderer;
	}
	else if (name == "physics")
	{
		return IComponent::Type::kPhysics;
	}
	else if (name == "collisionHandler")
	{
		return IComponent::Type::kCollisionHandler;
	}

	g_Logger.write(MyLogger::LogLevel::Game_Error, "Failed to parse component type from Xml file.");
	return IComponent::Type::kInvalid;
}
