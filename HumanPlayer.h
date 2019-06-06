#pragma once
#include "Player.h"
class HumanPlayer :
	public Player
{
public:
	HumanPlayer();
	~HumanPlayer();

	bool loadShipsFromFile(const std::string& filename);
	void buildAttackCoords();
};

