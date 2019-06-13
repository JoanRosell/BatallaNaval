#include "Ship.h"

Ship::Ship(int x, int y, int size, Ship_Orientation o) : deployed(false), size(size), activeCells(size), orientation(o)
{
	deployed = deploy({ x, y });
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
		cells.emplace(std::make_pair( firstCoord, true));
		for (int i = 0; i < size - 1; i++)
		{
			++firstCoord.second;
			cells.emplace(std::make_pair(firstCoord, true));
		}
		deployed = true;
		break;

	case Ship_Orientation::RIGHT:
		cells.emplace(std::make_pair(firstCoord, true));
		for (int i = 0; i < size - 1; i++)
		{
			++firstCoord.first;
			cells.emplace(std::make_pair(firstCoord, true));
		}
		deployed = true;
		break;

	case Ship_Orientation::UNDEFINED:
	default:
		break;
	}

	return deployed;
}

void Ship::registerHit(coord pos)
{
	auto it = cells.find(pos);

	if (it != cells.end())
	{
		it->second = false;
		activeCells--;
	}
}

bool Ship::isHit(const coord & c) const
{
	return cells.find(c) != cells.end();
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