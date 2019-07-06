#pragma once
#include <algorithm>
#include "Utilities.h"

class Action
{
public:
	Action() {}
	virtual ~Action() {}
	Action(const Action& a) {}

	virtual ActionOutcome execute() = 0;
	virtual Action* clone() = 0;
};
