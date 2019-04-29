#pragma once
#include "Event.h"

class MouseEvent :
	public Event
{
public:
	MouseEvent() = delete;
	MouseEvent(Event_Type type, Player_ID thisPlayer, int eventNumber, int input_X, int input_Y);
	~MouseEvent() {}
private:
	// Coordenada X, Y que guarda tal cual los valores que se le pasan
	coord rawPosition;
};


inline MouseEvent::MouseEvent(Event_Type type, Player_ID thisPlayer, int eventNumber, int input_X, int input_Y) : Event(type, thisPlayer, eventNumber),
	rawPosition(std::make_pair(input_X, input_Y)) { }


