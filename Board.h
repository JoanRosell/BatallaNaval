#pragma once
#include "InputHandler.h"
#include "Typedefs.h"
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
	std::vector<cell> attackedCoords;
	std::vector<Ship*> shipsDeployed;
	bool attendRequest(Action_Types request); // TO DO
};

