#pragma once
#include <utility>
#include "Ship.h"

enum class Ship_Orientation
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT,
	UNDEFINED
};

enum class Player_Type
{
	MACHINE,
	HUMAN
};

enum class Outcome_Type
{
	INVALID,
	WATER,
	SHIP_HIT,
	SHIP_DESTROYED
};

enum class Sprite_Type
{
	WATER,
	SHIP,
	DAMAGED_SHIP,
	DESTROYED_SHIP
};

struct coord
{
	unsigned short _x;
	unsigned short _y;

	bool operator==(const coord& rhs) const
	{
		return _x == rhs._x && _y == rhs._y;
	}
};


struct VisualizationCell
{
	coord coord;
	Sprite_Type spriteType;
	bool isHidden;
};

struct ActionOutcome
{
	Outcome_Type outcomeType;
	Ship affectedShip;
	coord coord;
};