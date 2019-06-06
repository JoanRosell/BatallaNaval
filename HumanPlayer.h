#pragma once
#include "Player.h"
#include "InputHandler.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer();
	~HumanPlayer();

	bool loadShipsFromFile(const std::string& filename);
	ActionOutcome takeAction();

private:
	void buildAttackCoords();
	InputHandler inputHandler;
};

