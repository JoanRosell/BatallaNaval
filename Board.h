#pragma once
#include "InputHandler.h"
#include "joc.h"
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
	std::vector<Cell> attackedCoords;
	std::vector<Ship*> shipsDeployed;
	bool attendRequest(Action_Types request); // TO DO
};

