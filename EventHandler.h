#pragma once
#include <vector>
#include "Typedefs.h"
#include "Event.h"
#include "MouseEvent.h"
#include "lib/libreria.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	bool catchEvents();
private:
	static int nEvents;
	std::vector<Event*> catchedEvents;
};

