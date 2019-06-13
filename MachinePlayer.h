#pragma once
#include "Player.h"
#include "ClickAction.h"
#include <vector>
#include <queue>
#include <random>

class MachinePlayer :
	public Player
{
public:
	MachinePlayer();
	~MachinePlayer();

	bool loadShipsFromFile(const std::string& file);
	ActionOutcome takeActionAgainst(Player* target);
	
private:
	std::uniform_int_distribution<int> distribution;
	std::random_device device;
	std::mt19937 rng;

	coord lastHitCoord;
	bool targetAcquired;
	std::queue<coord> atkQueue;
	Ship_Orientation currentAttackPattern;

	void updateAttackPattern(const coord & c);
	void buildAttackCoords();
	coord makeRandomAttack();

	void buildAttackQueue(const coord& c);
	void acquireTarget(const coord& c);
	void clearQueue();
};

