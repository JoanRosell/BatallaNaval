#pragma once
#include "Player.h"
#include "InputHandler.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer();
	~HumanPlayer() {}
	
	ActionOutcome takeActionAgainst(Player* target);
	bool loadShipsFromFile(const std::string& filename);

private:
	void buildAttackCoords();
	InputHandler inputHandler;
};

