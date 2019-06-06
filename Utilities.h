#pragma once
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
	SHIP_HIT,
	SHIP_DESTROYED
};

typedef std::pair<int, int> coord;

struct ActionOutcome
{
	Outcome_Type outcomeType;
	Ship affectedShip;
	coord coord;
};

struct VisualizationCell
{
	VisualizationCell(const coord& c, Sprite_Type t, bool v) : coord(c), spriteType(t), isVisible(v) {}
	coord coord;
	Sprite_Type spriteType;
	bool isVisible;
};