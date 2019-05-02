#include "UserInterface.h"

UserInterface::~UserInterface()
{
}

void UserInterface::update(std::vector<Ship> userShips, std::vector<Ship> machineShips)
{
	//	Esto habria que refactorizarlo en 2 o 3 metodos...
	if (!userShips.empty())
	{
		for (const auto& ship : userShips)
		{
			auto shipCoords = ship.getCoords();
			for (const auto& element : shipCoords)
			{
				int boardIndex = coordToIndex(element.second);
				auto currentSpriteType = deployBoard.at(boardIndex);

				if (currentSpriteType == Sprite_Type::NO_SPRITE)
					currentSpriteType = Sprite_Type::SHIP;
				
				if (!element.first && (currentSpriteType == Sprite_Type::SHIP))
					currentSpriteType = Sprite_Type::DAMAGED_SHIP;

				if (currentSpriteType == Sprite_Type::DAMAGED_SHIP)
					if (ship.isSank())
						currentSpriteType = Sprite_Type::DESTROYED_SHIP;
			}
		}
	}
}
