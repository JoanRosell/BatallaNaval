#pragma once
enum class Outcome_Type
{
	UNDEFINED,
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

struct Action_Outcome
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

	virtual Outcome_Type execute() = 0;
	bool isDone() const { return done; }
	
protected:
	bool done;
	
};
