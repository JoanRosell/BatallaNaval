#pragma once
enum class Action_Outcome
{
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

enum class Action_Type
{
	DEPLOY,
	ATTACK
};

class Action
{
public:
	Action() : done(false) {}
	Action(Action_Type t) : done(false), type(t) {}

	virtual ~Action() {}

	virtual Action_Outcome execute() = 0;
	bool isDone() const { return done; }
protected:
	bool done;
	Action_Type type;
};
