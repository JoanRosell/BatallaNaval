#include "ClickAction.h"

ClickAction::ClickAction(Player* source, Player* target, const coord& coordClicked) : Action(), 
	source(source), target(target), parameter(coordClicked), affectedShip(nullptr) {}

ClickAction::~ClickAction() { }

Action_Outcome ClickAction::execute()
{
	Action_Outcome outcome(Action_Outcome::UNDEFINED);

	if (!done)
	{ 
		
		auto attackCoords(source->getAttackCoords());
		bool validPosition(false);

		for (const auto& cell : attackCoords)
		{
			if (cell.first == parameter)
				if (!cell.second)
					validPosition = true;
		}

		if (validPosition)
		{
			source->updateAttackCoords(parameter);

			for (auto& ship : target->getShips())
				for (auto& cell : ship.getCells())
					if (cell.second == parameter)
					{
						ship.updateCell(parameter);
						affectedShip = &ship;

						if (ship.isDestroyed())
							outcome = Action_Outcome::SHIP_DESTROYED;
						else
							outcome = Action_Outcome::SHIP_HIT;
					}

			if (outcome == Action_Outcome::UNDEFINED)
				outcome = Action_Outcome::WATER;

		}
		else
			outcome = Action_Outcome::INVALID;
	}

	return outcome;
	
}
