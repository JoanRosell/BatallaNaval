#pragma once
#include "Player.h"
#include "ClickAction.h"
#include <vector>
#include <queue>
#include <random>
#include <chrono>

class MachinePlayer :
	public Player
{
public:
	MachinePlayer();
	~MachinePlayer() {}

	ActionOutcome takeActionAgainst(Player* target);
	bool loadShipsFromFile(const std::string& file);

private:
	std::uniform_int_distribution<int> distribution;
	std::default_random_engine rng;

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