#pragma once
enum class Action_Outcome
{
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

class Action
{
public:
	Action() : done(false) {}
	virtual ~Action() {}

	virtual Action_Outcome execute() = 0;
	bool isDone() const { return done; }
protected:
	bool done;
};
