#pragma once
#include "Player.h"
class MachinePlayer :
	public Player
{
public:
	MachinePlayer();
	~MachinePlayer();

	bool loadShipsFromFile(const std::string& file);
private:
	void buildAttackCoords();
};

