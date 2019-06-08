#pragma once
#include "Player.h"
class MachinePlayer :
	public Player
{
public:
	MachinePlayer();
	~MachinePlayer();

	bool loadShipsFromFile(const std::string& file);
	ActionOutcome takeAction(Player* target);

private:
	void buildAttackCoords();
};

