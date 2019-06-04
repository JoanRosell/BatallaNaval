#pragma once
#include <algorithm>

enum class Outcome_Type
{
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

struct ActionOutcome
{
	Outcome_Type outcomeType;
	Ship* affectedShip;
	cell affectedCell;
};

class Action
{
public:
	Action() : done(false) {}
	virtual ~Action() {}

	virtual ActionOutcome execute() = 0;
	bool isDone() const { return done; }
	
protected:
	bool done;
	
};
