#include "Ship.h"

Ship::~Ship()
{
}

bool Ship::deploy(Coord firstCoord)
{
	if (orientation == Ship_Orientation::UNDEFINED)

	return false;
}

void Ship::askOrientation()
{
	Ship_Orientation newOrientation;
	int input;
	std::cin >> input;
	// Traducir int a Ship_Orientation para poder actualizar el valor
	//newOrientation = input;
}
