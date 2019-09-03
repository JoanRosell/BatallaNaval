#pragma once
#include "PlayerBehaviour.h"
#include "ClickAction.h"
#include <vector>
#include <queue>
#include <random>
#include <chrono>

class MachineBehaviour :
	public PlayerBehaviour
{
public:
	MachineBehaviour(Player* p) : owner(p), distribution(0, 9), 
		targetAcquired(false), currentAttackPattern(Ship_Orientation::UNDEFINED)
	{
		rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
	}

	~MachineBehaviour();

	ActionOutcome execute(Player* target);

private:
	Player* owner;
	std::uniform_int_distribution<int> distribution;
	std::default_random_engine rng;
	coord lastHitCoord;
	bool targetAcquired;
	std::queue<coord> atkQueue;
	Ship_Orientation currentAttackPattern;

	coord makeRandomAttack();
	void acquireTarget(const coord& c);
	void buildAttackQueue(const coord& c);
	void clearQueue();
	void updateAttackPattern(const coord & c);
};