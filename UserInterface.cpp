#include "UserInterface.h"

UserInterface::~UserInterface()
{
}

void UserInterface::init(const std::vector<Ship>& userShips, const std::vector<Ship>& machineShips)
{
	//	Esto habria que refactorizarlo en 2 o 3 metodos...
	if (!userShips.empty())
	{
		for (const auto& ship : userShips)
		{
			auto cellVector = ship.getCoords();
			//	cell es una pareja (bool, coord)
			for (const auto& cell : cellVector)
			{
				int boardIndex = coordToIndex(cell.second);
				auto& currentSpriteType = deployBoard.at(boardIndex);

				if (currentSpriteType == Sprite_Type::NO_SPRITE)
					currentSpriteType = Sprite_Type::SHIP;
				
				if (!cell.first && (currentSpriteType == Sprite_Type::SHIP))
					currentSpriteType = Sprite_Type::DAMAGED_SHIP;

				if (currentSpriteType == Sprite_Type::DAMAGED_SHIP)
					if (ship.isSank())
						currentSpriteType = Sprite_Type::DESTROYED_SHIP;
			}
		}
	}

	if (!machineShips.empty())
	{
		for (const auto& ship : machineShips)
		{
			auto cellVector = ship.getCoords();
			//	cell es una pareja (bool, coord)
			for (const auto& cell : cellVector)
			{
				int boardIndex = coordToIndex(cell.second);
				auto& currentSpriteType = attackBoard.at(boardIndex);

				if (currentSpriteType == Sprite_Type::NO_SPRITE)
					currentSpriteType = Sprite_Type::SHIP;

				if (!cell.first && (currentSpriteType == Sprite_Type::SHIP))
					currentSpriteType = Sprite_Type::DAMAGED_SHIP;

				if (currentSpriteType == Sprite_Type::DAMAGED_SHIP)
					if (ship.isSank())
						currentSpriteType = Sprite_Type::DESTROYED_SHIP;
			}
		}
	}
}
