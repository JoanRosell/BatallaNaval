#include "UserInterface.h"

UserInterface::~UserInterface()
{
}

bool UserInterface::init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips)
{	
	bool machineBoardReady(false);
	bool humanBoardReady(false);

	humanBoardReady = loadBoard(humanBoard, userShips);
	machineBoardReady = loadBoard(machineBoard, machineShips);

	bool interfaceReady(false);
	if (humanBoardReady && machineBoardReady)
		interfaceReady = true;
	
	return interfaceReady;
}

void UserInterface::updateCell(coord pos, Sprite_Type newType, bool isHumanBoard)
{
	if (isHumanBoard)
	{
		humanBoard.at(coordToIndex(pos)) = newType;
	}
	else
	{
		machineBoard.at(coordToIndex(pos)) = newType;
	}
}

void UserInterface::updateShipStatus(Ship * ship, bool isHumanBoard)
{
	if (isHumanBoard)
	{
		updateBoard(humanBoard, *ship);
	}
	else
	{
		updateBoard(machineBoard, *ship);
	}
}

void UserInterface::printGraphics()
{
	boardImg.draw(0, 0);
	boardImg.draw(0, 10*MIDA_CASELLA);

	printBoard(machineBoard, 0, false);
	printBoard(humanBoard, MIDA_Y, true);
	
}

bool UserInterface::loadBoard(std::vector<Sprite_Type>& board, const std::vector<Ship>& ships)
{
	bool boardLoaded(false);

	if (!ships.empty())
	{
		for (const auto& ship : ships)
			if (ship.isDeployed()) // Asumimos que si, pero no está de mas comprobarlo en caso de que reutilicemos esta funcion
				updateBoard(board, ship);

		boardLoaded = true;
	}

	return boardLoaded;
}

// Actualiza la información del tablero de un barco entero
void UserInterface::updateBoard(std::vector<Sprite_Type>& board, const Ship& ship)
{
	auto cellVector(ship.getCells());
	bool shipIsDestroyed(ship.isDestroyed());

	for (const auto& cell : cellVector)
	{
		int index(coordToIndex(cell.second));
		updateSpriteType(board.at(index), !cell.first, shipIsDestroyed);
	}
}

void UserInterface::updateSpriteType(Sprite_Type & currentType, bool positionAttacked, bool shipIsDestroyed)
{	
	bool typeChanged(false);

	if (currentType == Sprite_Type::DAMAGED_SHIP)
		if (shipIsDestroyed)
		{
			currentType = Sprite_Type::DESTROYED_SHIP;
			typeChanged = true;
		}

	if (!typeChanged)
		if (positionAttacked)
		{
			switch (currentType)
			{
			case Sprite_Type::NO_SPRITE:
				currentType = Sprite_Type::WATER;
				break; 
			case Sprite_Type::SHIP:
				if (!shipIsDestroyed) // Cuando la ultima celda viva de un barco muere pasa de SHIP a DESTROYED_SHIP directamente
					currentType = Sprite_Type::DAMAGED_SHIP;
				else
					currentType = Sprite_Type::DESTROYED_SHIP;
				break;
			default:
				break;
			}
		}
		else
			if (currentType == Sprite_Type::NO_SPRITE)
				currentType = Sprite_Type::SHIP;
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
