#pragma once
/** \file GlarekApplicationLayer.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <memory>
#include "Application/ApplicationLayer.h"

/** \class GlarekApplicationLayer */
/** TODO: Class Purpose */
class GlarekApplicationLayer
	: public Engine::ApplicationLayer
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	GlarekApplicationLayer();

	/** Default Destructor */
	~GlarekApplicationLayer();

	virtual std::unique_ptr<Engine::IGameLayer> CraeteGameLayer() override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};