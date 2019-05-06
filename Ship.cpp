#include "Ship.h"

Ship::Ship(int x, int y, int size, Ship_Orientation o) : deployed(false),
destroyed(false), size(size), activeCells(size), orientation(o)
{
	deployed = deploy(std::make_pair(x, y));
}

Ship::~Ship()
{
}

//	TO DO: COMPROBAR SI SE PUEDE DESPLEGAR O NO
bool Ship::deploy(coord firstCoord) 
{
	bool deployed(false);

	switch (orientation)
	{
	case Ship_Orientation::TOP:
		myCells.push_back(std::make_pair(true, firstCoord));
		for (int i = 0; i < size-1; i++)
			myCells.emplace_back(std::make_pair(true, std::make_pair(firstCoord.first, ++firstCoord.second)));
		
		deployed = true;
		break;

	case Ship_Orientation::RIGHT:
		myCells.push_back(std::make_pair(true, firstCoord));
		for (int i = 0; i < size - 1; i++)
			myCells.emplace_back(std::make_pair(true, std::make_pair(++firstCoord.first, firstCoord.second)));
		
		deployed = true;
		break;

	case Ship_Orientation::BOTTOM:
		myCells.push_back(std::make_pair(true, firstCoord));
		for (int i = 0; i < size - 1; i++)
			myCells.emplace_back(std::make_pair(true, std::make_pair(firstCoord.first, --firstCoord.second)));

		deployed = true;
		break;

	case Ship_Orientation::LEFT:
		myCells.push_back(std::make_pair(true, firstCoord));
		for (int i = 0; i < size - 1; i++)
			myCells.emplace_back(std::make_pair(true, std::make_pair(--firstCoord.first, firstCoord.second)));

		deployed = true;
		break;

	case Ship_Orientation::UNDEFINED:
	default:
		break;
	}

	return deployed;
}

#ifndef __NOT_GRAPHICS
void Ship::askOrientation()
{
	while (orientation == Ship_Orientation::UNDEFINED)
	{
		SDL_Event input;
		SDL_WaitEvent(&input);
		if (input.type == SDL_KEYDOWN)
		{
			if (input.key.keysym.sym == KEYBOARD_T)
				orientation = Ship_Orientation::TOP;
		}
	}
}
#endif