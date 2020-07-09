#include "GlarekApplicationLayer.h"
#include "../Logic/GlarekGameLogic.h"
GlarekApplicationLayer::GlarekApplicationLayer()
{
	
}

GlarekApplicationLayer::~GlarekApplicationLayer()
{
	
}

std::unique_ptr<Engine::IGameLayer> GlarekApplicationLayer::CraeteGameLayer()
{
	return std::make_unique<GlarekGameLogic>();
}