#pragma once
#include <algorithm>
#include "Utilities.h"

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
