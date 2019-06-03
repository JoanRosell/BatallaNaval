#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked) {}

ClickAction::~ClickAction() { }

Action_Outcome ClickAction::execute()
{
	Action_Outcome result{ Outcome_Type::UNDEFINED, nullptr, parameter };

	if (!done)
	{ 
		auto attackCoords(source->getAttackCoords());
		bool validPosition(false);

		for (const auto& attackCoord : attackCoords)
		{
			if (attackCoord.coord == parameter)
				if (!attackCoord.isAlreadyAttacked)
					validPosition = true;
		}

		if (validPosition)
		{
			source->updateAttackCoords(parameter);

			for (auto& ship : target->getShips())
				for (auto& cell : ship.getCells())
					if (cell.coord == parameter)
					{
						ship.updateCell(parameter);
						result.affectedShip = &ship;

						if (ship.isDestroyed())
							result.outcomeType = Outcome_Type::SHIP_DESTROYED;
						else
							result.outcomeType = Outcome_Type::SHIP_HIT;
					}

			if (result.outcomeType == Outcome_Type::UNDEFINED)
				result.outcomeType = Outcome_Type::WATER;

		}
		else
			result.outcomeType = Outcome_Type::INVALID;
	}

	return result;
	
}
