#pragma once
#include <algorithm>
#include "Utilities.h"

class Action
{
public:
	Action() : done(false) {}
	virtual ~Action() {}
	Action(const Action& a) : done(a.done) {}

	virtual ActionOutcome execute() = 0;
	virtual Action* clone() = 0;

	bool isDone() const { return done; }
protected:
	bool done;
	
};
