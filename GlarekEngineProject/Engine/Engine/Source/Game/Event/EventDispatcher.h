#pragma once
/** \file EventDispatcher.h */
/** TODO: File Purpose */
// Created by Billy Graban
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>

#include "IEvent.h"
#include "../../Utility/Common.h"
/** \class EventDispatcher */
/** TODO: Class Purpose */
namespace Engine
{
	class EventDispatcher
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		//typedef EventCallback Standard function that takes an IEvent* and returns nothing
		typedef std::function<void(IEvent*)> EventCallback;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		/** Default Constructor */
		DLLEXP EventDispatcher() {};

		/** Default Destructor */
		DLLEXP ~EventDispatcher() {};

		//adds an event listener paired with an event id
		size_t AddEventListener(u32 id, EventCallback callback);

		//removes a listener from the bucket associated with that event id
		void RemoveEventListener(u32 id, size_t index);

		//prepare to process an event next frame
		void QueueEvent(std::unique_ptr<IEvent> pEvent) { m_eventQueue.push_back(std::move(pEvent)); }

		//process all events in the queue
		void ProcessEvents();

		//immediately Process Events.  Be aware of possible feedback loop.
		void ProcessEventImmediately(std::unique_ptr<IEvent> pEvent);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//map that associated callback functions to event ids
		std::unordered_map <u32, std::vector<EventCallback>> m_eventListeners;

		//queue of events to process next frame
		std::vector<std::unique_ptr<IEvent>> m_eventQueue;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}