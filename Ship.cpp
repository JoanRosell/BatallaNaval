#include "Ship.h"

Ship::~Ship()
{
}

void Ship::deployAt(int x, int y)
{
	if (!deployed)
	{
		grid_X = x;
		grid_Y = y;
		deployed = true;
	}
}

void Ship::draw() const
{
	if (deployed)
	{
		int current_X = grid_X;
		for (int i = 0; i < size; i++)
		{
			img->draw(current_X, grid_Y);
			current_X+=MIDA_CASELLA;
		}
	}
		
	
	if (sank)
	{
		// TO DO : ADD SHIP DESTROYED EFFECT
	}
}
