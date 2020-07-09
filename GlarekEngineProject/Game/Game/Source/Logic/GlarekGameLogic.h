#pragma once
/** \file GlarekGameLogic.h */
/** TODO: File Purpose */
// Created by Billy Graban

#include "Logic/IGameLayer.h"

/** \class GlarekGameLogic */
/** TODO: Class Purpose */
class GlarekGameLogic
	: public Engine::IGameLayer
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	/** Default Constructor */
	GlarekGameLogic() {};

	/** Default Destructor */
	~GlarekGameLogic() {};

	//get the game's name
	const char* GetGameName() const override { return "Glarek In Dungeon"; }

	//init
	bool Init(Engine::ApplicationLayer* pAppLayer) override;

	virtual void RegisterGameEvents() override {};

	void CreateDelayProcess(std::shared_ptr<Engine::Actor> pActor) override;

	void CreateMoveProcess(std::shared_ptr<Engine::Actor> pActor) override;

	void CreateDanceProcess(std::shared_ptr<Engine::Actor> pActor) override;

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