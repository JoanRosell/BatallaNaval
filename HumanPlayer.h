#pragma once
#include "Player.h"
#include "HumanBehaviour.h"

class HumanPlayer :
	public Player
{
public:
	HumanPlayer();
	~HumanPlayer() {}
	
	ActionOutcome takeActionAgainst(Player* target) { return behaviour->execute(target); }
	bool loadShipsFromFile(const std::string& filename);

private:
	void buildAttackCoords();
	
};

