#include "EventDispatcher.h"

size_t Engine::EventDispatcher::AddEventListener(u32 id, EventCallback callback)
{
	//find the vec associated with the event
	auto listenersItr = m_eventListeners.find(id);
	if (listenersItr == m_eventListeners.end()) //not find in the map
	{
		m_eventListeners.emplace(id, std::vector<EventCallback>{callback});
		return 0; //cause it's the first event of this type(ID), index 0
	}

	//find it
	//check for empty slot
	auto& listenerMap = listenersItr->second;
	for (size_t iListener = 0; iListener < listenerMap.size(); ++iListener)
	{
		if (listenerMap[iListener] == nullptr)
		{
			listenerMap[iListener] = callback;
			return iListener;
		}
	}

	//no empty slot
	listenerMap.push_back(callback);
	return listenerMap.size() - 1;
}

void Engine::EventDispatcher::RemoveEventListener(u32 id, size_t index)
{
	//find the listeners under the same type
	auto& listeners = m_eventListeners[id];
	if (index < listeners.size()) //find the listener
		listeners[index] = nullptr;
}

void Engine::EventDispatcher::ProcessEvents()
{
	//move all events here
	auto events = std::move(m_eventQueue);
	//for every event
	for (auto& pEvent : events)
	{
		//find all listeners associated with the event
		auto& listeners = m_eventListeners[pEvent->GetEventId()];
		//for every listener: execute the callback
		for (auto& listener : listeners)
		{
			if (listener)
				listener(pEvent.get());
		}
	}
}

void Engine::EventDispatcher::ProcessEventImmediately(std::unique_ptr<IEvent> pEvent)
{
	//find all listeners associated with the event
	auto& listeners = m_eventListeners[pEvent->GetEventId()];
	//for every listener: execute the callback
	for (auto& listener : listeners)
	{
		if (listener)
			listener(pEvent.get());
	}
}
