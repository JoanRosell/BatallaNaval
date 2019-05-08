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

void UserInterface::printBoards()
{
	boardImg.draw(0, 0);
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
				if (!shipIsDestroyed) // Cuando la ultima viva celda de un barco muere pasa de SHIP a DESTROYED_SHIP directamente
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