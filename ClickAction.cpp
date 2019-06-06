#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

ActionOutcome ClickAction::execute()
{
	ActionOutcome result{ Outcome_Type::INVALID, Ship(), parameter };
	
	if (!done && source->canAttackAt(parameter))
	{
		source->updateAtkCoords(parameter);

		result.outcomeType = target->processHit(parameter);

		if (result.outcomeType != Outcome_Type::WATER)
			result.affectedShip = target->getLastShipHit();
	}

	return result;
}

bool ClickAction::coordIsValid(const std::vector<attackCoord>::const_iterator & it, const std::vector<attackCoord>::const_iterator & end) const
{
	if (it != end)
		return !it->isAlreadyAttacked;
}