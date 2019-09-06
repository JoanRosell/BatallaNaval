#pragma once

struct ActionOutcome;

class Action
{
public:
	Action() {}
	virtual ~Action() {}
	Action(const Action& a) {}

	virtual ActionOutcome execute() = 0;
	virtual Action* clone() = 0;
};
