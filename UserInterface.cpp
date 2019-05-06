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

bool UserInterface::loadBoard(std::vector<Sprite_Type>& board, const std::vector<Ship>& ships)
{
	bool boardLoaded(false);

	if (!ships.empty())
	{
		for (const auto& ship : ships)
		{
			auto cellVector(ship.getCoords());
			bool shipIsDestroyed(ship.isSank());
			for (const auto& cell : cellVector)
				updateBoard(board, cell, shipIsDestroyed);
		}

		boardLoaded = true;
	}

	return boardLoaded;
}

void UserInterface::updateBoard(std::vector<Sprite_Type>& board, const std::pair<bool, coord>& cell, bool shipIsDestroyed)
{
	int index(coordToIndex(cell.second));
	board.at(index) = updateSpriteType(board.at(index), !cell.first, shipIsDestroyed);
}

Sprite_Type UserInterface::updateSpriteType(const Sprite_Type & oldType, bool positionAttacked, bool shipIsDestroyed)
{
	Sprite_Type newType(oldType);
	bool typeChanged(false);

	if (oldType == Sprite_Type::DAMAGED_SHIP)
		if (shipIsDestroyed)
		{
			newType = Sprite_Type::DESTROYED_SHIP;
			typeChanged = true;
		}

	if (!typeChanged)
		if (positionAttacked)
		{
			switch (oldType)
			{
			case Sprite_Type::NO_SPRITE:
				newType = Sprite_Type::WATER;
				break;
			case Sprite_Type::SHIP:
				newType = Sprite_Type::DAMAGED_SHIP;
				break;
			default:
				break;
			}
		}
		else
			if (oldType == Sprite_Type::NO_SPRITE)
				newType = Sprite_Type::SHIP;

	return newType;
}
