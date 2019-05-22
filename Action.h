#pragma once
class Action
{
public:
	Action() : done(false) {}
	virtual void execute() = 0;

protected:
	bool done;
};
