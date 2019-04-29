#pragma once
#include "EventHandler.h"

class Event
{
public:
	Event() = delete;
	Event(Event_Type type, Player_ID thisPlayer, int eventNumber);
	virtual ~Event() { }

protected:
	Event_Type type;
	int eventID;
	Player_ID source;
};


inline Event::Event(Event_Type type, Player_ID thisPlayer, int eventNumber) : type(type), 
source(thisPlayer), eventID(eventNumber) { }
