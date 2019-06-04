#pragma once
#include <algorithm>

enum class Outcome_Type
{
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

struct ActionOutcome // Test if storing a ptr to an object whose lifetime lasts longer gets destroyed upon self deletion
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
