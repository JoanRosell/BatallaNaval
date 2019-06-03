#include "UserInterface.h"

UserInterface::~UserInterface()
{
}

bool UserInterface::init(const std::vector<Ship>& humanShips, const std::vector<Ship>& machineShips)
{	
	bool boardsLoaded(false);

	if (!humanShips.empty() && !machineShips.empty())
	{
		for (const auto& ship : humanShips)
			if (ship.isDeployed()) // Asumimos que si, pero no está de mas comprobarlo en caso de que reutilicemos esta funcion
				updateShipStatus(ship, true);

		for (const auto& ship : machineShips)
			if (ship.isDeployed())
				updateShipStatus(ship, false);

		boardsLoaded = true;
	}

	return boardsLoaded;
}


void UserInterface::updateCell(VisualizationCell newCellState)
{
	
}

void UserInterface::updateShipStatus(const Ship& ship, bool defaultVisibility)
{
	for (const cell& shipCell : ship.getCells())
	{
		auto it = std::find_if(vBoard.begin(), vBoard.end(), 
			[&shipCell](const VisualizationCell& param) { return shipCell.coord == param.coord; }
		);

		if (it != vBoard.end())
		{
			if (ship.isDestroyed())
				it->spriteType = Sprite_Type::DESTROYED_SHIP;
			else
				if (shipCell.isHit && it->spriteType == Sprite_Type::SHIP)
				{
					it->spriteType = Sprite_Type::DAMAGED_SHIP;

					if (it->isHidden)
						it->isHidden = false;
				}
					
		}
		else
			vBoard.emplace_back(shipCell.coord, Sprite_Type::SHIP, defaultVisibility || shipCell.isHit);
	}
}
		

void UserInterface::printGraphics()
{
	boardImg.draw(0, 0);
	boardImg.draw(0, 10*MIDA_CASELLA);

	printBoard(machineBoard, 0, false);
	printBoard(humanBoard, MIDA_Y, true);
	
}

void UserInterface::printBoard(std::vector<Sprite_Type>& boardToPrint, int startY, bool visibility)
{
	int X(0);
	int Y(startY);

	for (const auto& spriteType : boardToPrint)
	{
		switch (spriteType)
		{
		case Sprite_Type::NO_SPRITE:
			break;
		case Sprite_Type::WATER:
			break;
		case Sprite_Type::SHIP:
			if (visibility)
				shipImg.draw(X, Y);
			break;
		case Sprite_Type::DAMAGED_SHIP:
			break;
		case Sprite_Type::DESTROYED_SHIP:
			break;
		default:
			break;
		}

		X += MIDA_CASELLA;

		if (X == MIDA_X)
		{
			X = 0;
			Y += MIDA_CASELLA;
		}
	}
}
