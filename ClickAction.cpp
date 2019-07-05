#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

ActionOutcome ClickAction::execute()
{
	ActionOutcome result;
	
	if (!done && source->canAttackAt(parameter))
	{
		result.coord = parameter;
		source->updateAtkCoords(parameter);

		result.outcomeType = target->processHit(parameter);

		if (result.outcomeType != Outcome_Type::WATER)
			result.affectedShip = target->getLastShipHit();
	}

	done = true;
	return result;
}