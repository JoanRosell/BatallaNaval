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
		registerPlayerShips(machineShips, true);

		boardsLoaded = true;
	}

	return boardsLoaded;
}

void UserInterface::updateChanges(const ActionOutcome & outcome)
{
	switch (outcome.outcomeType)
	{
	case Outcome_Type::WATER:
		updateCell(outcome.affectedCell.coord, Sprite_Type::WATER, false);
		break;
	case Outcome_Type::SHIP_HIT:
		updateCell(outcome.affectedCell.coord, Sprite_Type::DAMAGED_SHIP, !outcome.affectedCell.isHit);
		break;
	case Outcome_Type::SHIP_DESTROYED:
		updateShipDestroyed(*outcome.affectedShip);
		break;
	default:
		break;
	}
}

void UserInterface::registerPlayerShips(const std::vector<Ship>& ships, bool isHidden = false)
{
	for (const auto& ship : ships)
		for (const auto& cell : ship.getCells())
			updateCell(cell.coord, Sprite_Type::SHIP, isHidden);
}

void UserInterface::updateCell(coord coord, Sprite_Type newType, bool isHidden)
{
	auto it = std::find_if(vBoard.begin(), vBoard.end(),
		[&](const VisualizationCell& thisVCell) { return coord == thisVCell.coord; }
	);

	if (it != vBoard.end())
	{
		it->spriteType = newType;
		it->isHidden = isHidden;
	}
	
}

void UserInterface::updateShipDestroyed(const Ship & s)
{
	for (const auto& cell : s.getCells())
		updateCell(cell.coord, Sprite_Type::DESTROYED_SHIP, false);
}
		
//
//void UserInterface::printGraphics()
//{
//	boardImg.draw(0, 0);
//	boardImg.draw(0, 10*MIDA_CASELLA);
//
//	printBoard(machineBoard, 0, false);
//	printBoard(humanBoard, MIDA_Y, true);
//	
//}
//
//void UserInterface::printBoard(std::vector<Sprite_Type>& boardToPrint, int startY, bool visibility)
//{
//	int X(0);
//	int Y(startY);
//
//	for (const auto& spriteType : boardToPrint)
//	{
//		switch (spriteType)
//		{
//		case Sprite_Type::NO_SPRITE:
//			break;
//		case Sprite_Type::WATER:
//			break;
//		case Sprite_Type::SHIP:
//			if (visibility)
//				shipImg.draw(X, Y);
//			break;
//		case Sprite_Type::DAMAGED_SHIP:
//			break;
//		case Sprite_Type::DESTROYED_SHIP:
//			break;
//		default:
//			break;
//		}
//
//		X += MIDA_CASELLA;
//
//		if (X == MIDA_X)
//		{
//			X = 0;
//			Y += MIDA_CASELLA;
//		}
//	}
//}
