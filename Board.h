#pragma once
#include "InputHandler.h"
#include <iostream>
class Board
{
public:
	Board() : playerListener(nullptr)
	{}
	~Board();
	void attachListener(InputHandler* currentListener) { playerListener = currentListener; }
	void detachListener() { playerListener = nullptr; }
	bool processEvents();

private:
	InputHandler* playerListener;
	std::vector<std::pair<Coord, Ship*>> shipsDeployed;
	bool attendRequest(Request_Types request); // TO DO
	bool deployShipAt(Coord thisCoord); // TO DO
	bool assignCoordinates(Coord firstCoord, Ship* shipToDeploy); // TO DO
	Ship_Orientation askOrientation(); // TO DO
};

