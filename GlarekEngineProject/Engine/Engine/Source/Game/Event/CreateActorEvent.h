#pragma once
/** \file CreateActorEvent.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <string>

#include "IEvent.h"

/** \class CreateActorEvent */
/** TODO: Class Purpose */
namespace Engine
{
	class CreateActorEvent: public IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//id for CreateActorEvent
		static const u32 m_kEventId = 0;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		//constructor
		CreateActorEvent(std::string xmlFilepath) :m_xmlFilepath(xmlFilepath) {};

		//destructor
		~CreateActorEvent() {};


	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//the filepath to the xml data to build the actor from
		std::string m_xmlFilepath;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		//get the event id
		u32 GetEventId() override { return m_kEventId; }

		//get the event name
		const char* GetName() override{ return "CreateActorEvent"; }

		//get the filepath
		const char* GetXmlFilepath() { return m_xmlFilepath.c_str(); }

	};
}