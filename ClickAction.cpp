#include "ClickAction.h"

ClickAction::ClickAction(Player* target, const coord& coordClicked) : Action(), 
	target(target), parameter(coordClicked) {	}

ClickAction::~ClickAction()
{
}
