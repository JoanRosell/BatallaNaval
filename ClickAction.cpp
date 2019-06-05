#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

ActionOutcome ClickAction::execute()
{
	ActionOutcome result{ Outcome_Type::INVALID, nullptr, parameter };
	Outcome_Type outcomeType(Outcome_Type::INVALID);

	if (!done)
	{
		bool validPosition(false);

		if (source->canAttackAt(parameter))
		{
			source->updateAtkCoords(parameter);
			bool shipFound(false);

			if (target->fleetIsHit(parameter))
			{

			}
			else
			{
				outcomeType = Outcome_Type::WATER;
			}
			for (auto& ship : target->getShips())
			{
				auto shipIt = std::find_if(ship.getCells().begin(), ship.getCells().end(), [&](const cell& thisCell) {
					return thisCell.coord == parameter;
				});

				if (shipIt != ship.getCells().end())
				{
					shipFound = true;
					ship.registerHit(parameter);
					result.affectedShip = new Ship(ship);

					if (ship.isDestroyed())
						result.outcomeType = Outcome_Type::SHIP_DESTROYED;
					else
						result.outcomeType = Outcome_Type::SHIP_HIT;
				}

				if (shipFound)
					break;
			}

			if (!shipFound)
				result.outcomeType = Outcome_Type::WATER;
		}
	}

	return result;
}

bool ClickAction::coordIsValid(const std::vector<attackCoord>::const_iterator & it, const std::vector<attackCoord>::const_iterator & end) const
{
	if (it != end)
		return !it->isAlreadyAttacked;
}