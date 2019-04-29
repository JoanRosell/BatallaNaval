#include "EventHandler.h"



EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}

bool EventHandler::catchEvents()
{
	bool eventCatched(false);

	if (Mouse_getButLeft())
	{
		eventCatched = true;
		Event* newEvent = new MouseEvent(Event_Type::mouse_event, Player_ID::PLAYER_ONE, nEvents, Mouse_getX(), Mouse_getY());
		catchedEvents.push_back(newEvent);
	}

	return eventCatched;
}
