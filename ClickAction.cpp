#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

ActionOutcome ClickAction::execute()
{
	ActionOutcome result{ Outcome_Type::INVALID, nullptr, parameter };

	if (!done)
	{
		bool validPosition(false);
		
		auto atkCoordIt = std::find_if(source->getAttackCoords().begin(), source->getAttackCoords().end(), [&](const attackCoord& thisAtkCoord) {
			return thisAtkCoord.coord == parameter; 
		});

		if (coordIsValid(atkCoordIt, source->getAttackCoords().end()))
		{
			source->updateAttackCoords(parameter);
			bool shipFound(false);

			for (auto& ship : target->getShips())
			{
				auto shipIt = std::find_if(ship.getCells().begin(), ship.getCells().end(), [&](const cell& thisCell) {
					return thisCell.coord == parameter;
				});

				if (shipIt != ship.getCells().end())
				{
					shipFound = true;
					ship.updateCell(parameter);
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