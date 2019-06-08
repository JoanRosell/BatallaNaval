#include "UserInterface.h"

UserInterface::~UserInterface()
{
}

bool UserInterface::init(const std::vector<Ship>& humanShips, const std::vector<Ship>& machineShips)
{	
	bool boardsLoaded(false);

	if (!humanShips.empty() && !machineShips.empty())
	{
		registerPlayerShips(humanShips);
		registerPlayerShips(machineShips);

		boardsLoaded = true;
	}

	return boardsLoaded;
}

void UserInterface::updateChanges(const ActionOutcome & outcome)
{
	switch (outcome.outcomeType)
	{
	case Outcome_Type::WATER:
		updateCell(outcome.coord, Sprite_Type::WATER, true);
		break;
	case Outcome_Type::SHIP_HIT:
		updateCell(outcome.coord, Sprite_Type::SHIP_HIT, true);
		break;
	case Outcome_Type::SHIP_DESTROYED:
		updateShipDestroyed(outcome.affectedShip);
		break;
	default:
		break;
	}
}

void UserInterface::registerPlayerShips(const std::vector<Ship>& ships, bool isVisible)
{
	for (const auto& ship : ships)
		for (const auto& cell : ship.getCells())
			updateCell(cell.first, Sprite_Type::SHIP, isVisible);
}

void UserInterface::updateCell(coord coord, Sprite_Type newType, bool isVisible)
{
	auto it = std::find_if(vBoard.begin(), vBoard.end(),
		[&](const VisualizationCell& thisVCell) { return coord == thisVCell.coord; }
	);

	if (it != vBoard.end())
	{
		it->spriteType = newType;
		it->isVisible = isVisible;
	}
	else
	{
		vBoard.emplace_back(coord, newType, isVisible);
	}
}

void UserInterface::updateShipDestroyed(const Ship & s)
{
	for (const auto& cell : s.getCells())
		updateCell(cell.first, Sprite_Type::SHIP_DESTROYED, true);
}
		
void UserInterface::printGraphics()
{
	boardImg.draw(0, 0);
	boardImg.draw(0, 10*MIDA_CASELLA);
	printBoard();
}

void UserInterface::printBoard()
{
	for (const auto& vCell : vBoard)
		printCell(vCell);
}

void UserInterface::printCell(const VisualizationCell & vCell)
{
	if (vCell.isVisible)
		printSprite(vCell.coord, vCell.spriteType);
}

void UserInterface::printSprite(const coord & c, Sprite_Type type)
{
	switch (type)
	{
	case Sprite_Type::WATER:
		waterImg.draw(c.first*MIDA_CASELLA, c.second*MIDA_CASELLA);
		break;
	case Sprite_Type::SHIP:
		shipImg.draw(c.first*MIDA_CASELLA, c.second*MIDA_CASELLA);
		break;
	case Sprite_Type::SHIP_HIT:
		shipHitImg.draw(c.first*MIDA_CASELLA, c.second*MIDA_CASELLA);
		break;
	case Sprite_Type::SHIP_DESTROYED:
		shipDestroyedImg.draw(c.first*MIDA_CASELLA, c.second*MIDA_CASELLA);
		break;
	}
}
