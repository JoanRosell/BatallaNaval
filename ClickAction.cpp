#include "ClickAction.h"

ClickAction::ClickAction(Player* source, const coord& coordClicked) : Action(), 
	source(source), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

Action_Outcome ClickAction::execute()
{
	if (!done)
	{ }
	
}
