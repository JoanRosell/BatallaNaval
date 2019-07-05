#pragma once
#include "Ship.h"

enum class Player_Type
{
	MACHINE,
	HUMAN
};

enum class Outcome_Type
{
	INVALID, //	Al ser el primer elemento es el valor "por defecto"
	EXIT,
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

struct ActionOutcome
{
	ActionOutcome() //	No se usa initialization list para poder usar bracket initialization
	{
		outcomeType = Outcome_Type::INVALID; //	Innecesario, pero ayuda a entender el codigo
	}
	
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