#pragma once
#include "MachineBehaviour.h"
#include "ClickAction.h"

class MachinePlayer :
	public Player
{
public:
	MachinePlayer();
	~MachinePlayer() {}

	ActionOutcome takeActionAgainst(Player* target) { return this->behaviour->execute(target); }
	bool loadShipsFromFile(const std::string& file);

private:
	void buildAttackCoords(); //	To be implemented by factory

};